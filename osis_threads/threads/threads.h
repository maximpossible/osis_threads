#ifndef THREADS_H
#define THREADS_H

void* ReadThreadMutex(void* pqueue);
void* WriteThreadMutex(void* pqueue);

void* ReadThreadSemaphore(void* pqueue);
void* WriteThreadSemaphore(void* pqueue);

void* ReadThreadCond(void* pqueue);
void* WriteThreadCond(void* pqueue);

#endif
