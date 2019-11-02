#include <osis_threads/threads/threads.h>
#include <osis_threads/queue/queue.h>
#include <osis_threads/blob/blob.h>
#include <osis_threads/settings/settings.h>

void* ReadThreadMutex(void* pqueue)
{
    Queue* queue = (Queue*)pqueue;

    while (true)
    {
        Blob* blob = InitBlob();
        size_t read_bytes = ReadBlob(blob);
        if (read_bytes && read_bytes == GetBufSize())
        {
            queue->mutex->Lock();
            queue->PushBlob(blob);
            queue->mutex->Unlock();
        }
        else
        {
            queue->mutex->Lock();
            queue->SetActive(false);
            queue->mutex->Unlock();
            break;
        }
    }

    return NULL;
}

void* WriteThreadMutex(void* pqueue)
{
    Queue* queue = (Queue*)pqueue;

    while (true)
    {
        if (queue->Size())
        {
            queue->mutex->Lock();
            Blob* blob = queue->PopBlob();
            queue->mutex->Unlock();
            WriteBlob(blob);
        }

        if (0 == queue->Size() && false == queue->IsActive())
        {
            break;
        }
    }

    return NULL;
}

void* ReadThreadSemaphore(void* pqueue)
{
    Queue* queue = (Queue*)pqueue;

    while (true)
    {
        Blob* blob = InitBlob();
        size_t read_bytes = ReadBlob(blob);
        if (read_bytes && read_bytes == GetBufSize())
        {
            queue->semaphore->Wait();
            queue->PushBlob(blob);
            queue->semaphore->Post();
        }
        else
        {
            queue->semaphore->Wait();
            queue->SetActive(false);
            queue->semaphore->Post();
            break;
        }
    }

    return NULL;
}

void* WriteThreadSemaphore(void* pqueue)
{
    Queue* queue = (Queue*)pqueue;

    while (true)
    {
        if (queue->Size())
        {
            queue->semaphore->Wait();
            Blob* blob = queue->PopBlob();
            queue->semaphore->Post();
            WriteBlob(blob);
        }

        if (0 == queue->Size() && false == queue->IsActive())
        {
            break;
        }
    }

    return NULL;
}

void* ReadThreadCond(void* pqueue)
{
    Queue* queue = (Queue*)pqueue;
    while (true)
    {
        Blob* blob = InitBlob();
        size_t read_bytes = ReadBlob(blob);
        if (read_bytes && read_bytes == GetBufSize())
        {
            queue->mutex->Lock();
            queue->PushBlob(blob);
            queue->cond->Signal();
            queue->mutex->Unlock();
        }
        else
        {
            queue->mutex->Lock();
            queue->SetActive(false);
            queue->mutex->Unlock();
            break;
        }
    }

    return NULL;
}

void* WriteThreadCond(void* pqueue)
{
    Queue* queue = (Queue*)pqueue;
    while (true)
    {
        queue->mutex->Lock();

        if(!queue->Size())
        {
            queue->cond->Wait(queue->mutex);
        }
        
        Blob* blob = queue->PopBlob();
        queue->mutex->Unlock();
        
        WriteBlob(blob);

        if (0 == queue->Size() && false == queue->IsActive())
        {
            break;
        }
    }

    return NULL;
}
