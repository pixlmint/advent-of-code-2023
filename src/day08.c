#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day08.h"
#include "aoc.h"

void free_antenna_type_array(AntennaTypeArray *types) {
    for (int i = 0; i < types->length; i++) {
        free_point_array(types->types[i]->points);
        free(types->types[i]);
    }
    free_point_array(types->part1_antinodes);
    free_point_array(types->part2_antinodes);
    free(types->types);
    free(types);
}

void calculate_antinode_positions(Point *a, Point *b, Point *c, Point *d) {
    c->x = 2 * a->x - b->x;
    c->y = 2 * a->y - b->y;

    d->x = 2 * b->x - a->x;
    d->y = 2 * b->y - a->y;
}

PointArray *calculate_points_in_range(Point *start, Point *vec, int x_max, int y_max) {
    PointArray *points = init_point_array(10);
    int c = gcd((int) vec->x, (int) vec->y);
    // printf("Vec: (%f, %f)\n", vec->x, vec->y);
    // printf("GGT: %d\n", c);
    Point *min = malloc(sizeof(Point));
    Point *cur = malloc(sizeof(Point));
    min->x = vec->x / c;
    min->y = vec->y / c;
    cur->x = start->x;
    cur->y = start->y;

    while (cur->x < x_max && cur->x >= 0 && cur->y < y_max && cur->y >= 0) {
        // printf("Test (%f, %f)\n", cur->x, cur->y);

        if (point_array_index_of(points, cur) == -1) {
            append_coords(points, cur->x, cur->y);
        }

        cur->x += min->x;
        cur->y += min->y;
    }
    // cur->x = start->x;
    // cur->y = start->y;
    // while (cur->x <= x_max && cur->x >= 0 && cur->y <= y_max && cur->y >= 0) {
    //     cur->x -= min->x;
    //     cur->y -= min->y;

    //     if (point_array_index_of(points, cur) == -1) {
    //         append_coords(points, cur->x, cur->y);
    //     }
    // }

    free(min);
    free(cur);

    return points;
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
            map->data[(int) p->y][(int) p->x] = t->value;
        }
    }

    for (int i = 0; i < a->part2_antinodes->length; i++) {
        Point *p = a->part2_antinodes->points[i];
        map->data[(int) p->y][(int) p->x] = '#';
    }

    return map;
}

void count_antinodes(AntennaTypeArray *a) {
    for (int i = 0; i < a->length; i++) {
        AntennaType *ta = a->types[i];
        for (int j = 0; j < ta->points->length; j++) {
            Point *p = ta->points->points[j];
            for (int o = j + 1; o < ta->points->length; o++) {
                Point *p2 = ta->points->points[o];
                // Part 1
                PointArray *antinodes = init_point_array(2);
                append_coords(antinodes, 0, 0);
                append_coords(antinodes, 0, 0);

                calculate_antinode_positions(p, p2, antinodes->points[0], antinodes->points[1]);

                for (int pp = 0; pp < 2; pp++) {
                    Point *ab = antinodes->points[pp];
                    if (ab->x >= 0 && ab->x < a->max_x && ab->y >= 0 && ab->y < a->max_y) {
                        if (point_array_index_of(a->part1_antinodes, ab) == -1) {
                            append_coords(a->part1_antinodes, ab->x, ab->y); 
                        }
                    }
                }
                free_point_array(antinodes);

                // Part 2
                Point *vec = malloc(sizeof(Point));
                vec->x = p->x - p2->x;
                vec->y = p->y - p2->y;

                PointArray *p2_antinodes = calculate_points_in_range(p, vec, a->max_x, a->max_y);
                PointArray *merged = point_array_merge(a->part2_antinodes, p2_antinodes);
                free(a->part2_antinodes);
                free_point_array(p2_antinodes);
                a->part2_antinodes = merged;

                vec->x = p2->x - p->x;
                vec->y = p2->y - p->y;

                p2_antinodes = calculate_points_in_range(p2, vec, a->max_x, a->max_y);
                merged = point_array_merge(a->part2_antinodes, p2_antinodes);
                free(a->part2_antinodes);
                free_point_array(p2_antinodes);
                free(vec);
                a->part2_antinodes = merged;
            }
        }
    }
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
        types->types[antenna_pos] = t;
        types->length++;
    }

    append_coords(types->types[antenna_pos]->points, x, y);
}

AntennaTypeArray *read_map(FILE *file) {
    AntennaTypeArray *types = malloc(sizeof(AntennaTypeArray));
    types->types = malloc(sizeof(AntennaType*) * 100);
    types->length = 0;
    types->part1_antinodes = init_point_array(20);
    types->part2_antinodes = init_point_array(20);
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
    count_antinodes(map);
    IntMatrix *matrix = generate_matrix(map);
    print_matrix_as_char(matrix);
    free_matrix(matrix);

    printf("Part 1: %d\n", map->part1_antinodes->length);
    printf("Part 2: %d\n", map->part2_antinodes->length);
    free_antenna_type_array(map);
    fclose(file);
    return 0;
}
