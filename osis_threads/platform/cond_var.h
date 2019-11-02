#ifndef COND_VAR_H
#define COND_VAR_H

#include <osis_threads/platform/mutex.h>

typedef struct
{
    void (*Wait)(Mutex* pmtx);
    void (*Signal)(void);
} CondVar;

CondVar* InitCondVar(void);
void DestroyCondVar(CondVar* pcond);

#endif
