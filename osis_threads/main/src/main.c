#include <osis_threads/settings/settings.h>
#include <osis_threads/queue/queue.h>
#include <osis_threads/threads/threads.h>

#include <stdio.h>
#include <pthread.h>

int main(int argc, char** argv) // Вынести платформозависимую часть
{
    if (!InitSettings(argc, (const char**)argv))
    {
        return 1;
    }

    Queue* queue = InitQueue();

    pthread_t read_thread;
    pthread_t write_thread;

    pthread_create(&read_thread, NULL, ReadThread, queue);
    pthread_create(&write_thread, NULL, WriteThread, queue);

    pthread_join(read_thread, NULL);
    pthread_join(write_thread, NULL);

    return 0;
}
