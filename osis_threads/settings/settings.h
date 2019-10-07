#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <stdbool.h>

bool InitSettings(int argc, const char** argv);
const char* GetPathString(void);
FILE* GetDataFile(void);
FILE* GetOutFile(void);

#endif
