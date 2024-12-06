#ifndef DAY06_H
#define DAY06_H

#include "aoc.h"
#include <stdio.h>

#define OBSTACLE 50
#define EMPTY_SPACE 0
#define VISITED 1
#define DIRECTION_UP 1
#define DIRECTION_RIGHT 2
#define DIRECTION_DOWN 3
#define DIRECTION_LEFT 4

struct Room {
    int guard_x;
    int guard_y;
    int direction;
    int steps;
    struct IntMatrix *map;
};

int solve_day06(const char *input);
struct Room *read_room(FILE *file);
int solve(struct Room *room);
void free_room(struct Room *room);
void get_next_position(int direction, int *position);
int count_possible_obstacle_placements(struct Room *room);

#endif
