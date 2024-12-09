#ifndef DAY08_H
#define DAY08_H

#include <stdio.h>
#include "aoc.h"

typedef struct AntennaType {
    int value;
    PointArray *points;
} AntennaType;

typedef struct AntennaTypeArray{
    int max_x;
    int max_y;
    int length;
    AntennaType **types;
    PointArray *part1_antinodes;
    PointArray *part2_antinodes;
} AntennaTypeArray;

int solve_day08(const char *input);
AntennaTypeArray *read_map(FILE *file);
void register_antenna_position(AntennaTypeArray *types, int antenna_type, int x, int y);
void free_antenna_type_array(AntennaTypeArray *types);
void count_antinodes(AntennaTypeArray *a);
IntMatrix *generate_matrix(AntennaTypeArray *a);

#endif
