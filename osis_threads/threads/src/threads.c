#include <osis_threads/threads/threads.h>
#include <osis_threads/queue/queue.h>
#include <osis_threads/blob/blob.h>
#include <osis_threads/settings/settings.h>

void* ReadThread(void* pqueue)
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

void* WriteThread(void* pqueue)
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
