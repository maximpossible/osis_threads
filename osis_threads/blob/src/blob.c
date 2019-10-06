#include <osis_threads/blob/blob.h>
#include <osis_threads/settings/settings.h>

#include <malloc.h>

Blob* InitBlob(size_t size)
{
    Blob* blob = (Blob*)malloc(sizeof(Blob));
    blob->buf = malloc(sizeof(void*));
    blob->buf_size = size;
    return blob;
}

ssize_t ReadBlob(Blob* blob)
{
    return read(GetDataFile(), blob->buf, blob->buf_size);
}

ssize_t WriteBlob(Blob* blob)
{
    return write(GetOutFile(), blob->buf, blob->buf_size);
}

void DestroyBlob(void* pblob)
{
    if (pblob)
    {
        free(pblob);
        pblob = NULL;
    }
}
