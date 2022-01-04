#include "coordinates.h"

coordinate add(coordinate p1, coordinate p2) {
    coordinate p;
    p.x = p1.x + p2.x;
    p.y = p1.y + p2.y;
    return p;
}

char getstr2coor(char **xss, coordinate p) {
    return xss[p.y][p.x];
}
void setstr2coor(char ***xssp, coordinate p, char c) {
    char **xss = *xssp;
    xss[p.y][p.x] = c;
}

void coorcopy(coordinate *dest, const coordinate origin) {
    dest->x = origin.x;
    dest->y = origin.y;
}
