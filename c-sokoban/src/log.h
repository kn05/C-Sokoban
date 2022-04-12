#ifndef LOG_H_
#define FILE_H_

#include "string.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _log {
    int moves;
    int pushes;
    char *map;
} log;

void save(log, char *);

#endif