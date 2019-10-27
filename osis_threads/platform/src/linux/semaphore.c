#include <osis_threads/platform/semaphore.h>

#include <semaphore.h>

static struct 
{
    sem_t sem;

    Semaphore core;
} semaphore;

static void Wait(void)
{
    sem_wait(&semaphore.sem);
}

static void Post(void)
{
    sem_post(&semaphore.sem);
}

Semaphore* InitSemaphore(void)
{
    sem_init(&semaphore.sem, 0, 1);

    semaphore.core.Wait = Wait;
    semaphore.core.Post = Post;

    return &semaphore.core;
}

void DestroySemaphore(Semaphore* psem)
{
    if (!psem)
    {
        return;
    }
    if (&semaphore.core != psem)
    {
        return;
    }

    sem_destroy(&semaphore.sem);
}
