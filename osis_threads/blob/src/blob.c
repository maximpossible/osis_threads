#include <osis_threads/blob/blob.h>
#include <osis_threads/settings/settings.h>

#include <malloc.h>

Blob* InitBlob(void)
{
    Blob* blob = (Blob*)malloc(sizeof(Blob));
    blob->buf = malloc(sizeof(GetBufSize()));
    return blob;
}

ssize_t ReadBlob(Blob* blob)
{
    return fread(blob->buf, GetBufSize(), 1, GetDataFile());
}

ssize_t WriteBlob(Blob* blob)
{
    return fwrite(blob->buf, GetBufSize(), 1, GetOutFile());
}

void DestroyBlob(void* pblob)
{
    if (pblob)
    {
        free(pblob);
        pblob = NULL;
    }
}
