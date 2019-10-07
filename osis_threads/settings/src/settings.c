#include <osis_threads/settings/settings.h>

#include <stdlib.h>
#include <errno.h>

static struct
{
    const char* path;
    FILE* input_fd;
    FILE* output_fd;
    size_t buf_size;
} settings;

static const char* ParseArgs(int argc, const char** argv)
{
    if (argc == 1 || argc > 3)
    {
        printf("%s datafile [bytes_in_buffer]\n", argv[0]);
        return NULL;
    }

    settings.buf_size = 0;
    if (argc == 3)
    {
        settings.buf_size = atoi(argv[2]);
    }

    return argv[1];
}

bool InitSettings(int argc, const char** argv)
{
    settings.path = ParseArgs(argc, argv);
    if (!settings.buf_size)
    {
        settings.buf_size = 1;
    }

    settings.input_fd = fopen(settings.path, "rb");
    if (NULL == settings.input_fd)
    {
        printf("File %s can not be opened! Error %d\n", settings.path, errno);
        return false;
    }

    settings.output_fd = fopen("out", "wb");
    if (NULL == settings.input_fd)
    {
        printf("File \'out\' can not be opened!\n");
        return false;
    }

    return true;
}

const char* GetPathString(void)
{
    return settings.path;
}

FILE* GetDataFile(void)
{
    return settings.input_fd;
}

FILE* GetOutFile(void)
{
    return settings.output_fd;
}

size_t GetBufSize(void)
{
    return settings.buf_size;
}
