#ifndef QUEUE_H
#define QUEUE_H

#include <osis_threads/platform/mutex.h>
#include <osis_threads/platform/semaphore.h>
#include <osis_threads/platform/cond_var.h>
#include <osis_threads/blob/blob.h>

#include <stdbool.h>
#include <pthread.h>

typedef struct
{
    void (*PushBlob)(Blob* blob);
    Blob* (*PopBlob)(void);
    size_t (*Size)(void);
    void (*SetActive)(bool state);
    bool (*IsActive)(void);

    Mutex* mutex;
    Semaphore* semaphore;
    CondVar* cond;
} Queue;

Queue* InitQueue(void);
void DestroyQueue(Queue* pqueue);

#endif
