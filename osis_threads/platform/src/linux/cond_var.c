#include <osis_threads/platform/cond_var.h>

#include <pthread.h>

static struct 
{
    pthread_cond_t cond;

    CondVar core;
} cond_var;

static void Wait(Mutex* pmtx)
{
    pthread_cond_wait(&cond_var.cond, (pthread_mutex_t*)pmtx->Get());
}

static void Signal(void)
{
    pthread_cond_signal(&cond_var.cond);
}

CondVar* InitCondVar(void)
{
    pthread_cond_init(&cond_var.cond, NULL);

    cond_var.core.Wait = Wait;
    cond_var.core.Signal = Signal;

    return &cond_var.core;
}

void DestroyCondVar(CondVar* pcond)
{
    if (!pcond)
    {
        return;
    }
    if (&cond_var.core != pcond)
    {
        return;
    }

    pthread_cond_destroy(&cond_var.cond);
}
