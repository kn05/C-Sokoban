#ifndef STRINGS_H_
#define STRINGS_H_

#include "coordinates.h"
#include <stdlib.h>
#include <string.h>

int strcount(char *, const char *);
int split(char ***xssp, char *xs, const char *token);
coordinate str2dstr(char **xss, int height, const char *token);

#endif