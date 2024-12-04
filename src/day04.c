#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "day04.h"
#include "aoc.h"

int get_letter_mask(char letter) {
    switch (letter) {
        case 'X':
            return 1;
        case 'M':
            return 2;
        case 'A':
            return 3;
        case 'S':
            return 4;
    }
    return 0;
}

struct IntMatrix *create_mask_array(FILE *file) {
    fseek(file, 0, SEEK_SET);
    int lines = count_lines(file);
    char *first_line = malloc(sizeof(char) * 1000);
    fgets(first_line, 1000, file);
    fseek(file, 0, SEEK_SET);
    int line_length = strlen(first_line);
    if (first_line[line_length - 1] == '\n') {
        line_length -= 1;
    }
    free(first_line);

    struct IntMatrix *mask = init_int_matrix(lines, line_length);

    return mask;
}

void mask_input(FILE *file, struct IntMatrix *mask) {
    fseek(file, 0, SEEK_SET);
    char next_char = fgetc(file);
    int current_line = 0;
    int character_index = 0;
    while (next_char != EOF) {
        if (next_char == '\n') {
            current_line++;
            character_index = 0;
        } else {
            mask->data[current_line][character_index] = get_letter_mask(next_char);
            character_index++;
        }
        next_char = fgetc(file);
    }
    fseek(file, 0, SEEK_SET);
}

int count_in_row(int *row, int cols, int expected_matches) {
    int count = 0;
    for (int i = 0; i <= cols - expected_matches; i++) {
        if (row[i] == 1) {
            bool is_match = true;
            for (int j = 1; j < expected_matches; j++) {
                if (row[i + j] != j + 1) {
                    is_match = false;
                    break;
                }
            }
            if (is_match) count++;
        }
    }
    for (int i = cols - 1; i >= expected_matches - 1; i--) {
        if (row[i] == 1) {
            bool is_match = true;
            for (int j = 1; j < expected_matches; j++) {
                if (row[i - j] != j + 1) {
                    is_match = false;
                    break;
                } 
            }
            if (is_match) count++;
        }
    }

    return count;
}

int check_diagonally(struct IntMatrix *mask) {
    int count = 0;

    struct IntArray *arr;
    for (int i = 0; i < mask->cols; i++) {
        arr = get_diagonal_from_matrix(mask, 0, i);
        count += count_in_row(arr->values, arr->length, 4);
        free_array(arr);
    }
    for (int i = 1; i < mask->rows; i++) {
        arr = get_diagonal_from_matrix(mask, i, 0);
        count += count_in_row(arr->values, arr->length, 4);
        free_array(arr);
    }

    return count;
}

int count_total_occurrences(struct IntMatrix *mask) {
    int count_total = 0;
    int count_step = 0;
    for (int i = 0; i < mask->rows; i++) {
        count_step += count_in_row(mask->data[i], mask->cols, 4);
    }
    // printf("Step 1: %d, Total: %d\n", count_step, count_total);
    count_total += count_step;
    struct IntMatrix *transposed = transpose_int_matrix(mask);
    count_step = 0;
    for (int i = 0; i < transposed->rows; i++) {
        count_step += count_in_row(transposed->data[i], transposed->cols, 4);
    }
    // printf("Step 2: %d, Total: %d\n", count_step, count_total);
    count_total += count_step;

    count_step = check_diagonally(mask);
    // printf("Step 3: %d, Total: %d\n", count_step, count_total);
    count_total += count_step;

    struct IntMatrix *flipped = flip_int_matrix(mask);
    count_step = check_diagonally(flipped);
    // printf("Step 4: %d, Total: %d\n", count_step, count_total);
    count_total += count_step;

    free_matrix(transposed);
    free_matrix(flipped);

    return count_total;
}

void solve_part1(struct IntMatrix *mask) {
    int count_total = count_total_occurrences(mask);
    printf("Part One Solution: %d\n", count_total);
}

bool is_x_at_position(struct IntMatrix *mask, int y, int x) {
    if (mask->data[y][x] != 2) {
        return false;
    }

    int ul = mask->data[y - 1][x - 1];
    int ur = mask->data[y - 1][x + 1];
    int ll = mask->data[y + 1][x - 1];
    int lr = mask->data[y + 1][x + 1];

    if (ul == 2 || ur == 2 || ll == 2 || lr == 2) {
        return false;
    }

    if (ul + lr != 4 || ur + ll != 4) {
        return false;
    }

    return true;
}

int count_crosses(struct IntMatrix *mask) {
    int crosses = 0;

    for (int i = 1; i < mask->rows - 1; i++) {
        for (int j = 1; j < mask->cols - 1; j++) {
            if (is_x_at_position(mask, i, j)) crosses++;
        }
    }

    return crosses;
}


void solve_part2(struct IntMatrix *mask) {
    mask = clone_int_matrix(mask);

    for (int i = 0; i < mask->rows; i++) {
        for (int j = 0; j < mask->cols; j++) {
            mask->data[i][j] = mask->data[i][j] - 1;
        }
    }

    printf("Part 2 Solution: %d\n", count_crosses(mask));

    free_matrix(mask);
}

int solve_day04(const char *input_path) {
    FILE *file = fopen(input_path, "r");

    if (!file) {
        fprintf(stderr, "%s\n", input_path);
        return -1;
    }

    struct IntMatrix *mask = create_mask_array(file);
    printf("%d x %d matrix\n", mask->rows, mask->cols);
    mask_input(file, mask);
    fclose(file);

    solve_part1(mask);
    solve_part2(mask);

    free_matrix(mask);

    return 0;
}
