#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aoc.h"
#include "day06.h"

void get_next_position(int direction, int* position) {
    switch (direction) {
        case DIRECTION_UP:
            position[1] -= 1;
            return;
        case DIRECTION_RIGHT:
            position[0] += 1;
            return;
        case DIRECTION_DOWN:
            position[1] += 1;
            return;
        case DIRECTION_LEFT:
            position[0] -= 1;
            return;
    }

    fprintf(stderr, "Invalid direction: %d\n", direction);
}

void solve(struct Room *room) {
    int iter = 0;
    while (true) {
        int position[] = {room->guard_x, room->guard_y};
        get_next_position(room->direction, position);
        if (position[0] >= room->map->rows || position[1] >= room->map->cols || position[0] < 0 || position[1] < 0) {
            return;
        }
        int value_at_position = room->map->data[position[1]][position[0]];
        if (value_at_position == OBSTACLE) {
            int old_direction = room->direction;
            room->direction += 1;
            if (room->direction > 4) {
                room->direction = 1;
            }
            // printf("Iter #%d, Turning right, old direction: %d, new direction: %d\n", iter, old_direction, room->direction);
        } else if (value_at_position == EMPTY_SPACE) {
            room->steps++;
            room->map->data[position[1]][position[0]] = VISITED;
            room->guard_x = position[0];
            room->guard_y = position[1];
            // printf("Iter #%d, visited (%d, %d)\n", iter, room->guard_x, room->guard_y);
        } else {
            room->guard_x = position[0];
            room->guard_y = position[1];
            // printf("Iter #%d, (%d, %d)\n", iter, room->guard_x, room->guard_y);
        }
        iter++;
    }
}

struct Room *init_room() {
    struct Room *room = malloc(sizeof(struct Room));
    room->steps = 0;
    room->guard_x = 0;
    room->guard_y = 0;
    room->direction = 0;

    return room;
}

void free_room(struct Room *room) {
    free_matrix(room->map);
    free(room);
}

struct Room *read_room(FILE *file) {
    struct Room *room = init_room();
    int num_lines = count_lines(file);
    char *line = calloc(1000, sizeof(char));
    fgets(line, 1000, file);
    int num_cols = strlen(line);
    fseek(file, 0, SEEK_SET);
    if (line[num_cols - 1] == '\n') {
        line[num_cols - 1] = '\0';
        num_cols--;
    }

    struct IntMatrix *map = init_int_matrix(num_lines, num_cols);

    for (int i = 0; i < num_lines; i++) {
        fgets(line, 1000, file);

        for (int j = 0; j < num_cols; j++) {
            char c = line[j];
            if (c == '^') {
                room->guard_x = j;
                room->guard_y = i;
                room->direction = DIRECTION_UP;
                room->steps = 1;
                map->data[i][j] = VISITED;
            } else if (c == '#') {
                map->data[i][j] = OBSTACLE;
            } else {
                map->data[i][j] = EMPTY_SPACE;
            }
        }

        memset(line, 0, 1000);
    }

    free(line);
    room->map = map;

    return room;
}

int solve_day06(const char *input) {
    FILE *file = fopen(input, "r");
    struct Room * room = read_room(file);
    fclose(file);
    solve(room);

    printf("Solution: %d steps\n", room->steps);

    free_room(room);
    return 0; // Example solution
}
