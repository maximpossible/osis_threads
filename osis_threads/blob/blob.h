#ifndef BLOB_H
#define BLOB_H

#include <unistd.h>
#include <stdbool.h>

typedef struct
{
    void* buf;
    size_t buf_size;
} Blob;

Blob* InitBlob(size_t size);
ssize_t ReadBlob(Blob* blob);
ssize_t WriteBlob(Blob* blob);
void DestroyBlob(void* pblob);

#endif
