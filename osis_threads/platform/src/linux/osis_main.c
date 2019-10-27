#include <osis_threads/platform/osis_main.h>
#include <osis_threads/queue/queue.h>   
#include <osis_threads/threads/threads.h>

#include <pthread.h>

int OsisMain(int argc, const char** argv)
{
    Queue* queue = InitQueue();

    pthread_t read_thread;
    pthread_t write_thread;

    pthread_create(&read_thread, NULL, ReadThreadMutex, queue);
    pthread_create(&write_thread, NULL, WriteThreadMutex, queue);

    pthread_join(read_thread, NULL);
    pthread_join(write_thread, NULL);

    return 0;
}
