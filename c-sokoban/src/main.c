#include "file.h"

void clean();

int main() {
    char f_menu_path[] = "c-sokoban/files/menu.txt";
    char *menu = load_file(f_menu_path);
    printf("%s\n", menu);
    return 0;
}

void clean() {
    printf("\e[1;1H\e[2J");
}
