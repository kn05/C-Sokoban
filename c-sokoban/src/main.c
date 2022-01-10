#include "file.h"
#include "strings.h"

const char *player_s = "P";
const char *block_s = "#";
const char *filled_box_s = "@";
const char *empty_box_s = "O";
const char *goal_s = "!";
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

int push(char ***mapp, coordinate box, coordinate dir) {
    coordinate box_want = add(box, dir);
    if (getstr2coor(*mapp, box_want) == ' ') {
        setstr2coor(mapp, box_want, *empty_box_s);
        if (getstr2coor(*mapp, box) == *empty_box_s) {
            setstr2coor(mapp, box, ' ');
        } else if (getstr2coor(*mapp, box) == *filled_box_s) {
            setstr2coor(mapp, box, *goal_s);
        }
        return 1;
    } else if (getstr2coor(*mapp, box_want) == *goal_s) {
        setstr2coor(mapp, box_want, *filled_box_s);
        if (getstr2coor(*mapp, box) == *empty_box_s) {
            setstr2coor(mapp, box, ' ');
        } else if (getstr2coor(*mapp, box) == *filled_box_s) {
            setstr2coor(mapp, box, *goal_s);
        }
        return 1;
    }
    return 0;
}

void move(char ***mapp, coordinate *playerp, char command, int *moves_p, int *pushes_p) {
    coordinate dir;
    switch (command) {
    case 'W':
    case 'w':
        dir = (coordinate){.x = 0, .y = -1};
        break;
    case 'A':
    case 'a':
        dir = (coordinate){.x = -1, .y = 0};
        break;
    case 'S':
    case 's':
        dir = (coordinate){.x = 0, .y = 1};
        break;
    case 'D':
    case 'd':
        dir = (coordinate){.x = 1, .y = 0};
        break;
    default:
        break;
    }
    coordinate player_want = add(*playerp, dir);

    if (getstr2coor(*mapp, player_want) == ' ' || getstr2coor(*mapp, player_want) == *goal_s) {
        coorcopy(playerp, player_want);
        (*moves_p)++;
        return;
    } else if (getstr2coor(*mapp, player_want) == *filled_box_s || getstr2coor(*mapp, player_want) == *empty_box_s) {
        if (push(mapp, player_want, dir)) {
            coorcopy(playerp, player_want);
            (*moves_p)++;
            (*pushes_p)++;
            return;
        }
        return;
    }
    return;
}

void play() {
    clean();
    char map_path[] = "c-sokoban/files/map.txt";
    char *map_file = load_file(map_path);
    char **map;
    int mapheight = split(&map, map_file, endline_s);

    char log_path[] = "c-sokoban/files/log.txt";
    coordinate player;
    int moves;
    int pushes;
    {
        FILE *f_log = fopen(log_path, "r");
        if (f_log == NULL) {
            ;
        } else {
            fscanf(f_log, "%*s %d %d", &player.x, &player.y);
            fscanf(f_log, "%*s %d", &moves);
            fscanf(f_log, "%*s %d", &pushes);
        }
        fclose(f_log);
    }

    gotoxy(0, 0);
    printstr2(map, mapheight);
    printf("%d %d\n", player.x, player.y);
    gotoxy(player.x, player.y);
    printf("%s", player_s);
    gotoxy(0, mapheight + 2);

    while (1) {
        char command;
        scanf(" %c", &command);

        if (command == 'e' || command == 'E') {
            exit(0);
        } else {
            move(&map, &player, command, &moves, &pushes);
            clean();
            gotoxy(0, 0);
            printstr2(map, mapheight);
            printf("\nmoves: %d \tpushes: %d\n", moves, pushes);
            gotoxy(player.x, player.y);
            printf("%s", player_s);
            gotoxy(0, mapheight + 3);
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
    printf("%c[%d;%df", 0x1B, y + 1, x + 1);
}
