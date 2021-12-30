#include "file.h"

char *load_file(char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        printf("file pointer is null.\n");
        return NULL;
    }
    long size = fsize(f);
    char *string = malloc(size + 1);
    fread(string, size, 1, f);
    fclose(f);
    string[size] = '\0';

    return string;
}

long fsize(FILE *fp) {
    if (fp == NULL) {
        printf("fsize: file pointer is null");
        return 0;
    }
    long size = 0;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size;
}