#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdbool.h>

bool InitSettings(int argc, const char** argv);
const char* GetPathString(void);
int GetDataFile(void);
int GetOutFile(void);

#endif
