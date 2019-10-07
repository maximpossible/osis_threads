#include <osis_threads/platform/osis_main.h>
#include <osis_threads/settings/settings.h>

int main(int argc, char** argv)
{
    if (!InitSettings(argc, (const char**)argv))
    {
        return 1;
    }
    return OsisMain(argc, (const char**)argv);
}
