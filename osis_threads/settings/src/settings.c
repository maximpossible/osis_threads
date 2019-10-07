/* 
    TODO: Количество за раз считываемых байт лучше парсить и хранить
    в этой структуре, получая доступ через GetBufSize()
*/

#include <osis_threads/settings/settings.h>

#include <errno.h>

static struct
{
    const char* path;
    FILE* input_fd;
    FILE* output_fd;
} settings;

static const char* ParseArgs(int argc, const char** argv)
{
    if (argc == 1)
    {
        printf("Error. Not enough arguments\n");
        return NULL;
    }

    return argv[1];
}

bool InitSettings(int argc, const char** argv)
{
    settings.path = ParseArgs(argc, argv);
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
