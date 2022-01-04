#ifndef COORDINATES_H_
#define COORDINATES_H_

typedef struct _coordinate {
    int x;
    int y;
} coordinate;

coordinate add(coordinate p1, coordinate p2);
char getstr2coor(char **xss, coordinate p);
void setstr2coor(char ***xssp, coordinate p, char c);
void coorcopy(coordinate *dest, const coordinate origin);

#endif