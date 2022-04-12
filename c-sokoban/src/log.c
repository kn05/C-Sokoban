#include "log.h"

void save(log l, char *path) {
    FILE *fp = fopen(path, "w");

    fprintf(fp, "moves %d\n", l.moves);
    fprintf(fp, "pushes %d\n", l.pushes);
    fprintf(fp, "%s", l.map);

    fclose(fp);
}
