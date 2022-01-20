#include "file.h"
#include "play.h"
#include "strings.h"

void menu();
void record();

int main() {
    menu();
    return 0;
}

void menu() {
    char path[] = "c-sokoban/files/menu.txt";
    char *menu = load_file(path);
    printf("%s\n", menu);

    char mode;
    scanf("%c", &mode);

    if (mode == 'P' || mode == 'p') {
        play();
    } else if (mode == 'R' || mode == 'r') {
        record();
    } else if (mode == 'E' || mode == 'e') {
        exit(0);
    } else {
        printf("Press one of the P, R or E keys.");
    }
    return;
}

void record() {
    printf("record");
    return;
}
