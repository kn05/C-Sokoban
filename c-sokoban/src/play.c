#include "play.h"

const char *VOID = " ";
const char *WALL = "#";
const char *GOAL = ".";
const char *BALL = "*";
const char *IN_BALL = "$";
const char *PLAYER = "@";
const char *IN_PLAYER = "+";
const char *ENDLINE = "\n";

void clean() {
    printf("\e[1;1H\e[2J");
}

void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y + 1, x + 1);
}

char lose(char c) {
    if (c == *PLAYER || c == *BALL) {
        return *VOID;
    }
    if (c == *IN_PLAYER || c == *IN_BALL) {
        return *GOAL;
    }
    return 0;
}
char gain(char c, char _c) {
    if (c == *PLAYER || c == *IN_PLAYER) {
        if (_c == *VOID) {
            return *PLAYER;
        }
        if (_c == *GOAL) {
            return *IN_PLAYER;
        }
    }
    if (c == *BALL || c == *IN_BALL) {
        if (_c == *VOID) {
            return *BALL;
        }
        if (_c == *GOAL) {
            return *IN_BALL;
        }
    }
    return 0;
}

void _move(char ***ptrMap, coordinate p, coordinate _p, char pStat, char _pStat) {
    setstr2coor(ptrMap, p, lose(pStat));
    setstr2coor(ptrMap, _p, gain(pStat, _pStat));
}

int _push(char ***ptrMap, coordinate player, coordinate ball, coordinate dir) {
    coordinate _player = add(player, dir);
    coordinate _ball = add(ball, dir);
    char ballStat = getstr2coor(*ptrMap, ball);
    char _ballStat = getstr2coor(*ptrMap, _ball);
    if (_ballStat == *VOID || _ballStat == *GOAL) {
        _move(ptrMap, ball, _ball, ballStat, _ballStat);
        char playerStat = getstr2coor(*ptrMap, player);
        char _playerStat = getstr2coor(*ptrMap, _player);
        _move(ptrMap, player, _player, playerStat, _playerStat);
        return 1;
    }
    return 0;
}

void _step(char ***ptrMap, coordinate *ptrPlayer, char command, int *ptrMoves, int *ptrPushes) {
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

    coordinate _player = add(*ptrPlayer, dir);
    char playerStat = getstr2coor(*ptrMap, *ptrPlayer);
    char _playerStat = getstr2coor(*ptrMap, _player);
    if (_playerStat == *IN_BALL || _playerStat == *BALL) { //push를 실행할지 여부.
        if (_push(ptrMap, *ptrPlayer, _player, dir)) {
            coorcopy(ptrPlayer, _player);
            (*ptrMoves)++;
            (*ptrPushes)++;
            return;
        }
        return;
    }
    if (_playerStat == *VOID || _playerStat == *GOAL) {
        _move(ptrMap, *ptrPlayer, _player, playerStat, _playerStat);
        coorcopy(ptrPlayer, _player);
        (*ptrMoves)++;
        return;
    }
    return;
}

int complete(char **map, int mapheight) {
    if (str2count(map, mapheight, BALL) == 0) {
        return 1;
    }
    return 0;
}

void play() {
    clean();
    char map_path[] = "c-sokoban/files/map.txt";
    char *map_file = load_file(map_path);
    char **map;
    int mapheight = split(&map, map_file, ENDLINE);
    char log_path[] = "c-sokoban/files/log.txt";
    coordinate player;
    int moves;
    int pushes;
    {
        FILE *f_log = fopen(log_path, "r");
        if (f_log == NULL) {
            ;
        } else {
            fscanf(f_log, "%*s %d", &moves);
            fscanf(f_log, "%*s %d", &pushes);
        }
        fclose(f_log);
    }
    player = str2dstr(map, mapheight, PLAYER);

    gotoxy(0, 0);
    printstr2(map, mapheight);
    printf("%d %d\n", player.x, player.y);
    printf("moves: %d \tpushes: %d\n", moves, pushes);
    while (1) {
        char command;
        scanf(" %c", &command);

        if (command == 'e' || command == 'E') {
            exit(0);
        } else {
            _step(&map, &player, command, &moves, &pushes);
            clean();
            gotoxy(0, 0);
            printstr2(map, mapheight);
            printf("%d %d\n", player.x, player.y);
            printf("moves: %d \tpushes: %d\n", moves, pushes);
            if (complete(map, mapheight)) {
                printf("Congratulations! \n");
                break;
            }
        }
    }
    return;
}