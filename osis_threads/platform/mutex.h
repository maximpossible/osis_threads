#ifndef MUTEX_H
#define MUTEX_H

typedef struct
{
    void (*Lock)(void);
    void (*Unlock)(void);
    void* (*Get)(void);
} Mutex;

Mutex* InitMutex(void);
void DestroyMutex(Mutex* pmtx);

#endif
