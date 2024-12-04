#ifndef DAY04_H
#define DAY04_H

#include <stdio.h>
int solve_day04(const char *input);
struct IntMatrix *create_mask_array(FILE *file);
int get_letter_mask(char letter);
void mask_input(FILE *file, struct IntMatrix *mask);
int count_in_row(int *row, int cols, int expected_matches);
int check_diagonally(struct IntMatrix *mask);
int count_total_occurrences(struct IntMatrix *mask);

#endif
