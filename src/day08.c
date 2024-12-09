#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day08.h"
#include "aoc.h"

void free_antenna_type_array(AntennaTypeArray *types) {
    for (int i = 0; i < types->length; i++) {
        free_point_array(types->types[i]->points);
    }
    free_point_array(types->antinodes);
    free(types->types);
    free(types);
}

void calculate_antinode_positions(Point *a, Point *b, Point *c, Point *d) {
    c->x = 2 * a->x - b->x;
    c->y = 2 * a->y - b->y;

    d->x = 2 * b->x - a->x;
    d->y = 2 * b->y - a->y;
}

IntMatrix *generate_matrix(AntennaTypeArray *a) {
    IntMatrix *map = init_int_matrix(a->max_x, a->max_y);
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            map->data[i][j] = '.';
        }
    }

    for (int i = 0; i < a->length; i++) {
        AntennaType *t = a->types[i];
        for (int j = 0; j < t->points->length; j++) {
            Point *p = t->points->points[j];
            map->data[p->y][p->x] = t->value;
        }
    }

    for (int i = 0; i < a->antinodes->length; i++) {
        Point *p = a->antinodes->points[i];
        map->data[p->y][p->x] = '#';
    }

    return map;
}

int count_antinodes(AntennaTypeArray *a) {
    for (int i = 0; i < a->length; i++) {
        AntennaType *ta = a->types[i];
        for (int j = 0; j < ta->points->length; j++) {
            Point *p = ta->points->points[j];
            for (int o = j + 1; o < ta->points->length; o++) {
                Point *p2 = ta->points->points[o];
                PointArray *antinodes = init_point_array(2);
                append_coords(antinodes, 0, 0);
                append_coords(antinodes, 0, 0);

                calculate_antinode_positions(p, p2, antinodes->points[0], antinodes->points[1]);

                for (int pp = 0; pp < 2; pp++) {
                    Point *ab = antinodes->points[pp];
                    if (ab->x >= 0 && ab->x < a->max_x && ab->y >= 0 && ab->y < a->max_y) {
                        // printf("Found Antinode for %c: (%d, %d)\n", ta->value, ab->x, ab->y);
                        if (point_array_index_of(a->antinodes, ab) == -1) {
                            append_coords(a->antinodes, ab->x, ab->y); 
                        }
                    }
                }
                free_point_array(antinodes);
            }
        }
    }
    return a->antinodes->length;
}

void register_antenna_position(AntennaTypeArray *types, int antenna_type, int x, int y) {
    int antenna_pos = -1;
    for (int i = 0; i < types->length; i++) {
        if (types->types[i]->value == antenna_type) {
            antenna_pos = i;
            break;
        }
    }

    if (antenna_pos == -1) {
        AntennaType *t = malloc(sizeof(AntennaType));
        t->value = antenna_type;
        t->points = init_point_array(20);
        antenna_pos = types->length;
        types->antinodes = init_point_array(10);
        types->types[antenna_pos] = t;
        types->length++;
    }

    append_coords(types->types[antenna_pos]->points, x, y);
}

AntennaTypeArray *read_map(FILE *file) {
    AntennaTypeArray *types = malloc(sizeof(AntennaTypeArray));
    types->types = malloc(sizeof(AntennaType*) * 100);
    types->length = 0;
    int lines = count_lines(file);
    int cols = count_columns(file);
    types->max_x = cols;
    types->max_y = lines;
    char *line = calloc(sizeof(char), cols + 2);

    for (int i = 0; i < lines; i++) {
        fgets(line, cols + 2, file);

        for (int j = 0; j < cols; j++) {
            char pos = line[j];
            if (pos == '.') {
                pos = 0;
            } else {
                register_antenna_position(types, pos, j, i);
            }
        }

        memset(line, 0, cols + 2);
    }
    free(line);

    return types;
}

int solve_day08(const char *input) {
    FILE *file = fopen(input, "r");
    AntennaTypeArray *map = read_map(file);
    int count = count_antinodes(map);
    printf("Count: %d\n", count);
    IntMatrix *matrix = generate_matrix(map);
    print_matrix_as_char(matrix);
    free_matrix(matrix);
    free_antenna_type_array(map);
    fclose(file);
    return 0;
}
