#ifndef BLOB_H
#define BLOB_H

#include <unistd.h>
#include <stdbool.h>

typedef struct
{
    void* buf;
} Blob;

Blob* InitBlob(void);
ssize_t ReadBlob(Blob* blob);
ssize_t WriteBlob(Blob* blob);
void DestroyBlob(void* pblob);

#endif
