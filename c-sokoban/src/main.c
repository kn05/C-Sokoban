#include "file.h"
#include "strings.h"

void clean();
void menu();
void play();
void record();
void gotoxy(int, int);
int strcount(char *, const char *);
int split(char ***, char *, const char *);

int main() {
    menu();
    return 0;
}

void clean() {
    printf("\e[1;1H\e[2J");
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

void play() {
    clean();
    char path[] = "c-sokoban/files/map.txt";
    char *mapfile = load_file(path);

    //#, *, @, % 등을 block, goal, box, player 등으로 변환시키거나 반대로 변환. (만약 기호를 바꿀 생각이 없다면 굳이 필요없음)
    //const char player = '#'으로 충분할지도.

    char **map;
    int mapheight = split(&map, mapfile, "\n");

    printf("%d\n", mapheight);
    for (int i = 0; i < mapheight - 1; i++) {
        printf("%s\n", map[i]);
    }
    coordinate player = str2dstr(map, mapheight, "%");
    printf("%d %d\n", player.x, player.y);
    //maybe need map(f, xs)

    //px, py = find_player(map)  //maybe need coordinate struct?
    //move player

    return;
}

void record() {
    clean();
    printf("record");
    return;
}

void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}
