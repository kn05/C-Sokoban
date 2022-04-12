#ifndef STRINGS_H_
#define STRINGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _coordinate {
    int x;
    int y;
} coordinate;

coordinate add(coordinate p1, coordinate p2);
char getstr2coor(char **xss, coordinate p);
void setstr2coor(char ***xssp, coordinate p, char c);
void coorcopy(coordinate *dest, const coordinate origin);

int strcount(char *, const char);
int str2count(char **str2, int height, const char);
int split(char ***xssp, char *xs, const char);
char *join(char **, int, char);
coordinate str2dstr(char **, int, const char);
void printstr2(char **, int);

#endif