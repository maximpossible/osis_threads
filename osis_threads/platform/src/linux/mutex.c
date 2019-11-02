#include <osis_threads/platform/mutex.h>

#include <pthread.h>

static struct 
{
    pthread_mutex_t mtx;

    Mutex core;
} mutex;

static void Lock(void)
{
    pthread_mutex_lock(&mutex.mtx);
}

static void Unlock(void)
{
    pthread_mutex_unlock(&mutex.mtx);
}

static void* Get(void)
{
    return (void*)&mutex.mtx;
}

Mutex* InitMutex(void)
{
    pthread_mutex_init(&mutex.mtx, NULL);

    mutex.core.Lock = Lock;
    mutex.core.Unlock = Unlock;
    mutex.core.Get = Get;

    return &mutex.core;
}

void DestroyMutex(Mutex* pmtx)
{
    if (!pmtx)
    {
        return;
    }
    if (&mutex.core != pmtx)
    {
        return;
    }

    pthread_mutex_destroy(&mutex.mtx);
}
