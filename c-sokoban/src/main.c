#include "file.h"
#include "strings.h"

const char *player_s = "P";
const char *block_s = "#";
const char *box_s = "@";
const char *goal_s = "O";
const char *endline_s = "\n";

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

int move(char ***mapp, coordinate *playerp, char command) {
    coordinate command_dir;

    switch (command) {
    case 'W':
    case 'w':
        command_dir = (coordinate){.x = 0, .y = -1};
        break;
    case 'A':
    case 'a':
        command_dir = (coordinate){.x = -1, .y = 0};
        break;
    case 'S':
    case 's':
        command_dir = (coordinate){.x = 0, .y = 1};
        break;
    case 'D':
    case 'd':
        command_dir = (coordinate){.x = 1, .y = 0};
        break;
    default:
        break;
    }

    coordinate player_want = add(*playerp, command_dir);

    //map NULL check

    if (getstr2coor(*mapp, player_want) == ' ') {
        setstr2coor(mapp, *playerp, ' ');
        setstr2coor(mapp, player_want, *player_s);
        coorcopy(playerp, player_want);
        return 1;
    } else if (getstr2coor(*mapp, player_want) == *box_s) {
        coordinate box_want = add(player_want, command_dir);
        if (getstr2coor(*mapp, box_want) == ' ') {
            setstr2coor(mapp, box_want, *box_s);
            setstr2coor(mapp, player_want, *player_s);
            setstr2coor(mapp, *playerp, ' ');
            coorcopy(playerp, player_want);
            return 1;
        }
    }

    return 0;
}

void play() {
    clean();
    char path[] = "c-sokoban/files/map.txt";
    char *mapfile = load_file(path);

    char **map;
    int mapheight = split(&map, mapfile, endline_s);

    for (int i = 0; i < mapheight; i++) {
        printf("%s\n", map[i]);
    }
    coordinate player = str2dstr(map, mapheight, player_s);
    printf("%d %d\n", player.x, player.y);

    while (1) {
        char command;
        scanf(" %c", &command);

        if (command == 'e' || command == 'E') {
            exit(0);
        } else {
            move(&map, &player, command);
            clean();
            printstr2(map, mapheight);
            printf("%d %d\n", player.x, player.y);
        }
    }
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
