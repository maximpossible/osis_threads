#include <osis_threads/platform/osis_main.h>
#include <osis_threads/queue/queue.h>   
#include <osis_threads/threads/threads.h>

#include <stdio.h>
#include <pthread.h>

int OsisMain(int argc, const char** argv)
{
    Queue* queue = InitQueue();

    pthread_t read_thread;
    pthread_t write_thread;

    int chose;
    do
    {
        printf("Select synchronization primitive:\n");
        printf("1. Mutex\n");
        printf("2. Semaphore\n");

        chose = getchar();
        if (chose >= '1' && chose <= '2')
        {
            break;
        }
    } while (true);

    printf("out");
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
    }

    pthread_join(read_thread, NULL);
    pthread_join(write_thread, NULL);

    return 0;
}
