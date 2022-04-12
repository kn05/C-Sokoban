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
void setstr2coor(char ***xssPtr, coordinate p, char c) {
    (*xssPtr)[p.y][p.x] = c;
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

int split(char ***xssPtr, char *xs, const char token) {
    char _token[2];
    _token[0] = token;
    _token[1] = 0;

    if (*xssPtr == NULL) {
        ; //
    }
    if (xs == NULL) {
        ; //
    }

    int size = strcount(xs, token) + 1;
    *xssPtr = malloc(sizeof(char *) * size);

    (*xssPtr)[0] = strtok(xs, _token);
    for (int i = 1; i < size; i++) {
        (*xssPtr)[i] = strtok(NULL, _token);
    }
    return size;
}

char *join(char **str2, int height, char _endline) {
    int length = 0;
    for (int i = 0; i < height; i++) {
        length += strlen(str2[i]) + 1;
    }
    char endline[2];
    endline[0] = _endline;
    endline[1] = 0;
    char *str = malloc(sizeof(char) * length);
    for (int i = 0; i < height; i++) {
        strcat(str, str2[i]);
        strcat(str, endline);
    }
    return str;
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