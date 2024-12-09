#ifndef DAY09_H
#define DAY09_H

#include <sys/types.h>
#include "aoc.h"

typedef struct Block {
    int size;
    int index;
} Block;

typedef struct DiscMap {
    int length;
    int max_length;
    Block **blocks;
} DiscMap;

int solve_day09(const char *input);
DiscMap *read_disc_map(char *map);
void free_disc_map(DiscMap *map);
void print_disc_map(DiscMap *map);
u_long calc_checksum(IntArray *arr);
IntArray *shift_map(DiscMap *map);
IntArray *shift_map_without_fragmentation(DiscMap *map);

#endif
