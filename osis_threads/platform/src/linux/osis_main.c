#include <osis_threads/platform/osis_main.h>
#include <osis_threads/queue/queue.h>   
#include <osis_threads/threads/threads.h>

#include <stdio.h>
#include <pthread.h>
#include <malloc.h>

int OsisMain(int argc, const char** argv)
{
    Queue* queue = InitQueue();

    pthread_t read_thread;
    pthread_t write_thread;

    char chose;
    do
    {
        printf("Select synchronization primitive:\n");
        printf("1. Mutex\n");
        printf("2. Semaphore\n");
        printf("3. Conditional variable\n");
        printf("\n");
        printf("Choice: ");

        chose = getchar();
        if (chose >= '1' && chose <= '3')
        {
            break;
        }
    } while ((chose = getchar()) == '\n');

    switch (chose)
    {
    case '1':
        pthread_create(&read_thread, NULL, ReadThreadMutex, queue);
        pthread_create(&write_thread, NULL, WriteThreadMutex, queue);
        break;
    case '2':
        pthread_create(&read_thread, NULL, ReadThreadSemaphore, queue);
        pthread_create(&write_thread, NULL, WriteThreadSemaphore, queue);
        break;
    case '3':
        pthread_create(&read_thread, NULL, ReadThreadCond, queue);
        pthread_create(&write_thread, NULL, WriteThreadCond, queue);
        break;
    }

    pthread_join(read_thread, NULL);
    pthread_join(write_thread, NULL);

    return 0;
}
