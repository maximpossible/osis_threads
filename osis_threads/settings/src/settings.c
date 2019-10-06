/* 
    TODO: Либо вынести платфоромзависимую часть, 
    либо использовать стандартную библиотеку 
*/

#include <osis_threads/settings/settings.h>

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

static struct
{
    const char* path;
    int input_fd;
    int output_fd;
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
    settings.input_fd = open(settings.path, O_RDONLY);
    if (-1 == settings.input_fd)
    {
        printf("File %s can not be opened! Error %d\n", settings.path, errno);
        return false;
    }

    settings.output_fd = creat("out", S_IRWXU);
    if (-1 == settings.input_fd)
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

int GetDataFile(void)
{
    return settings.input_fd;
}

int GetOutFile(void)
{
    return settings.output_fd;
}
