#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct
{
    void (*Wait)(void);
    void (*Post)(void);
} Semaphore;

Semaphore* InitSemaphore(void);
void DestroySemaphore(Semaphore* psem);

#endif
