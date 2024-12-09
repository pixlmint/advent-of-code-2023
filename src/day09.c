#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "aoc.h"
#include "day09.h"

void free_disc_map(DiscMap *map) {
    for (int i = 0; i < map->length; i++) {
        free(map->blocks[i]);
    }
    free(map->blocks);
    free(map);
}

void print_disc_map(DiscMap *map) {
    // printf("Disc Map of length %d\n", map->length);
    for (int i = 0; i < map->length; i++) {
        char c;
        if (map->blocks[i]->index == -1) {
            c = '.';
        } else {
            c = int_to_char(map->blocks[i]->index);
        }
        for (int j = 0; j < map->blocks[i]->size; j++) {
            printf("%c", c);
        }
    }
    printf("\n");
}

void print_disc_map_array(DiscMap *map) {
    printf("Disc Map of length %d\n", map->length);
    for (int i = 0; i < map->length; i++) {
        Block *blk = map->blocks[i];
        printf("| %dx %d |", blk->size, blk->index);
    }
    printf("\n");
}

void append_block(DiscMap *map, Block *b) {
    if (map->max_length <= map->length) {
        map->max_length += map->max_length / 2;
        map->blocks = realloc(map->blocks, sizeof(Block) * map->max_length);
    }
    map->blocks[map->length++] = b;
}

void insert_block(DiscMap *map, Block *b, int insert_pos) {
    if (map->max_length <= map->length) {
        map->max_length += map->max_length / 2;
    }

    Block **new_list = malloc(map->max_length * sizeof(Block));

    int modifier = 0;
    for (int i = 0; i <= map->length; i++) {
        if (i == insert_pos) {
            new_list[i] = b;
            modifier = 1;
        } else {
            new_list[i] = map->blocks[i - modifier];
        }
    }
    map->length += 1;
    free(map->blocks);
    map->blocks = new_list;
}

void block_delete(DiscMap *map, int index) {
    Block **new_list = malloc(map->max_length * sizeof(Block));

    int modifier = 0;
    for (int i = 0; i < map->length; i++) {
        if (i != index) {
            new_list[i - modifier] = map->blocks[i];
        } else {
            modifier++;
        }
    }
    map->length -= modifier;

    free(map->blocks);
    map->blocks = new_list;
}

void reorder_blocks(DiscMap *map) {
    int delete_count = 1;
    while (delete_count > 0) {
        delete_count = 0;
        for (int i = 1; i < map->length - 1; i++) {
            Block *cur = map->blocks[i];
            Block *prev = map->blocks[i - 1];
            Block *next = map->blocks[i + 1];

            if (cur->index == prev->index) {
                prev->size += cur->size;
                block_delete(map, i);
                delete_count++;
                break;
            }

            if (cur->index == next->index) {
                cur->size += next->size;
                block_delete(map, i + 1);
                delete_count++;
                break;
            }
        }
    }
}

DiscMap *init_disc_map(int length) {
    DiscMap *dm = malloc(sizeof(DiscMap));
    dm->blocks = malloc(sizeof(Block) * length);
    dm->length = 0;
    dm->max_length = length;

    return dm;
}

DiscMap *read_disc_map(char *map) {
    DiscMap *dm = init_disc_map(20);
    int i = 0;
    while (map[i] != '\0') {
        Block *b = malloc(sizeof(Block));
        b->size = char_to_int(map[i]);
        int index;
        if (i % 2 == 0) {
            b->index = i / 2;
        } else {
            b->index = -1;
        }
        append_block(dm, b);
        i++;
    }

    return dm;
}

IntArray *shift_map(DiscMap *map) {
    IntArray *out = init_int_array(map->length);
    for (int i = 0; i < map->length; i++) {
        Block *blk = map->blocks[i];
        for (int x = 0; x < blk->size; x++) {
            if (blk->index == -1) {
                for (int j = map->length - 1; j > i; j--) {
                    Block *tmp = map->blocks[j];
                    if (tmp->index != -1 && tmp->size > 0) {
                        int_array_append(out, tmp->index);
                        tmp->size--;
                        break;
                    }
                }
            } else {
                int_array_append(out, blk->index);
            }
        }
    }

    return out;
}

void swap_blocks(DiscMap *map, int i_from, int i_to) {
    if (i_from >= map->length || i_to >= map->length) {
        fprintf(stderr, "Invalid from/ to indexes provided for array of length %d: %d, %d\n", map->length, i_from, i_to);
        return;
    }
    Block *from = map->blocks[i_from];
    Block *to = map->blocks[i_to];

    if (from->size > to->size) {
        fprintf(stderr, "Block of size %d may not be put in place of block of smaller size %d\n", from->size, to->size);
        return;
    }

    // printf("Swapping Block Value %d from %d to %d\n", from->index, i_from, i_to);
    map->blocks[i_from] = to;
    map->blocks[i_to] = from;

    if (from->size < to->size) {
        Block *insert = malloc(sizeof(Block));
        insert->size = to->size - from->size;
        insert->index = to->index;
        insert_block(map, insert, i_to + 1);
        to->size -= insert->size;
    }
}

IntArray *shift_map_without_fragmentation(DiscMap *map) {
    for (int i = map->length - 1; i >= 0; i--) {
        Block *blk = map->blocks[i];
        if (blk->index != -1) {
            for (int j = 0; j < i; j++) {
                Block *tmp = map->blocks[j];
                if (tmp->index == -1 && tmp->size >= blk->size) {
                    swap_blocks(map, i, j);
                    reorder_blocks(map);
                    break;
                }
            }
        }
    }

    IntArray *out = init_int_array(map->length);

    for (int i = 0; i < map->length; i++) {
        int val = 0;
        Block *blk = map->blocks[i];
        if (blk->index != -1) {
            val = blk->index;
        }
        for (int x = 0; x < blk->size; x++)  {
            int_array_append(out, val);
        }
    }

    return out;
}

u_long calc_checksum(IntArray *arr) {
    u_long checksum = 0;

    for (int i = 0; i < arr->length; i++) {
        checksum += i * arr->values[i];
    }

    return checksum;
}

int solve_day09(const char *fp) {
    char *input = read_file(fp);
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    DiscMap *map = read_disc_map(input);
    IntArray *shifted = shift_map(map);
    u_long checksum = calc_checksum(shifted);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Checksum: %ld\n", checksum);
    printf("Execution Time: %fs\n", cpu_time_used);

    free_disc_map(map);
    free_array(shifted);

    start = clock();
    map = read_disc_map(input);
    shifted = shift_map_without_fragmentation(map);
    checksum = calc_checksum(shifted);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Checksum (2): %ld\n", checksum);
    printf("Execution Time: %fs\n", cpu_time_used);

    free_disc_map(map);
    free_array(shifted);

    return 0;
}
