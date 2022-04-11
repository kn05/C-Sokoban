#include "strings.h"

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
    (*xssp)[p.y][p.x] = c;
}

void coorcopy(coordinate *dest, const coordinate origin) {
    dest->x = origin.x;
    dest->y = origin.y;
}

int strcount(char *xs, const char token) {
    int cnt = 0;
    char *ptr = strchr(xs, token);
    while (ptr != NULL) {
        ptr = strchr(ptr + 1, token);
        cnt++;
    }
    return cnt;
}

int str2count(char **str2, int height, const char token) {
    int cnt = 0;
    for (int i = 0; i < height; i++) {
        char *ptr = strchr(str2[i], token);
        while (ptr != NULL) {
            ptr = strchr(ptr + 1, token);
            cnt++;
        }
    }
    return cnt;
}

int split(char ***xssp, char *xs, const char token) {
    char _token[2];
    _token[0] = token;
    _token[1] = 0;

    if (*xssp == NULL) {
        ; //
    }
    if (xs == NULL) {
        ; //
    }

    int size = strcount(xs, token) + 1;
    *xssp = malloc(sizeof(char *) * size);

    (*xssp)[0] = strtok(xs, _token);
    for (int i = 1; i < size; i++) {
        (*xssp)[i] = strtok(NULL, _token);
    }
    return size;
}

coordinate str2dstr(char **xss, int height, const char token) {
    coordinate p;
    for (int i = 0; i < height; i++) {
        char *ptr = strchr(xss[i], token);
        if (ptr != NULL) {
            p.y = i;
            p.x = ptr - xss[i];
            break;
        }
    }
    return p;
}

void printstr2(char **str2, int height) {
    for (int i = 0; i < height; i++) {
        printf("%s\n", str2[i]);
    }
}