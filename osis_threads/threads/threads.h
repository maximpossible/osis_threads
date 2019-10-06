#ifndef THREADS_H
#define THREADS_H

void* ReadThread(void* pqueue);
void* WriteThread(void* pqueue);

#endif
