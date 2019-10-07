#include <osis_threads/queue/queue.h>

#include <malloc.h>
#include <stdlib.h>

typedef struct Cell Cell;

struct Cell
{
    Blob* blob;
    Cell* next_cell;
};

static struct 
{
    Cell* head;
    Cell* tail;
    size_t cells_count;
    bool is_active; 

    Queue core;
} queue;

static void PushBlob(Blob* blob)
{
    if (!blob)
    {
        return;
    }

    if (NULL == queue.head)
    {
        queue.head = (Cell*)malloc(sizeof(Cell));
        queue.head->blob = blob;
        queue.head->next_cell = NULL;
        queue.tail = queue.head;
    }
    else
    {
        queue.tail->next_cell = (Cell*)malloc(sizeof(Cell));
        queue.tail = queue.tail->next_cell;
        queue.tail->blob = blob;
        queue.tail->next_cell = NULL; 
    }
    ++queue.cells_count;
}

static Blob* PopBlob(void)
{
    if (!queue.cells_count)
    {
        return NULL;
    }

    Blob* blob = queue.head->blob;
    Cell* new_head = queue.head->next_cell;
    free(queue.head);
    queue.head = new_head;
    --queue.cells_count;

    return blob;
}

static size_t Size(void)
{
    return queue.cells_count;
}

static void SetActive(bool state)
{
    queue.is_active = state;
}

static bool IsActive(void)
{
    return queue.is_active;
}

Queue* InitQueue(void)
{
    queue.core.mutex = InitMutex();

    queue.head = NULL;
    queue.cells_count = 0;
    queue.is_active = true;

    queue.core.PushBlob     = PushBlob;
    queue.core.PopBlob      = PopBlob;
    queue.core.Size         = Size;
    queue.core.SetActive    = SetActive;
    queue.core.IsActive     = IsActive;
    
    return &queue.core;
}

void DestroyQueue(Queue* pqueue)
{
    if (NULL == pqueue)
    {
        return;
    }
    if (&queue.core != pqueue)
    {
        return;
    }
    
    if (queue.core.mutex)
    {
        DestroyMutex(queue.core.mutex);
    }

    Cell* next_cell;
    Cell* curr_cell = queue.head;
    while (curr_cell)
    {
        next_cell = curr_cell->next_cell;
        DestroyBlob(curr_cell->blob);
        free(curr_cell);
        curr_cell = next_cell;
    }

    queue.cells_count = 0;
    queue.is_active = false;
}
