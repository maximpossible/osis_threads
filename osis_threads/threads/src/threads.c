#include <osis_threads/threads/threads.h>
#include <osis_threads/queue/queue.h>
#include <osis_threads/blob/blob.h>

void* ReadThread(void* pqueue)
{
    Queue* queue = (Queue*)pqueue;

    while (true)
    {
        Blob* blob = InitBlob(8);
        ssize_t read_bits = ReadBlob(blob);
        if (read_bits)
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
            return NULL;
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
            return NULL;
        }
    }

    return NULL;
}
