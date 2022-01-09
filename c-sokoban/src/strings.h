#ifndef STRINGS_H_
#define STRINGS_H_

#include "coordinates.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcount(char *, const char *);
int split(char ***xssp, char *xs, const char *);
coordinate str2dstr(char **, int, const char *);
void printstr2(char **, int);

#endif