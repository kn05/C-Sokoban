#include "strings.h"

int strcount(char *xs, const char *token) {
    int cnt = 0;
    char *ptr = strstr(xs, token);
    while (ptr != NULL) {
        ptr = strstr(ptr + 1, token);
        cnt++;
    }
    return cnt;
}

int split(char ***xssp, char *xs, const char *token) {
    if (*xssp == NULL) {
        ; //
    }
    if (xs == NULL) {
        ; //
    }

    int size = strcount(xs, token) + 1;
    *xssp = malloc(sizeof(char *) * size);

    (*xssp)[0] = strtok(xs, token);
    for (int i = 1; i < size; i++) {
        (*xssp)[i] = strtok(NULL, token);
    }
    return size;
}

coordinate str2dstr(char **xss, int height, const char *token) {
    coordinate p;
    for (int i = 0; i < height; i++) {
        char *ptr = strstr(xss[i], token);
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