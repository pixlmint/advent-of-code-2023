#ifndef DAY07_H
#define DAY07_H

#include "aoc.h"
#include <sys/types.h>
struct CalculationsTable {
    int num_calculations;
    u_long *results;
    struct LongArray **inputs;
};

int solve_day07(const char *input);
void free_calculations_table(struct CalculationsTable *table);
struct CalculationsTable *init_calculations_table(int num_calculations);
void parse_calculation_row(char *calc, u_long *result, struct LongArray *input);
bool is_valid_calculation(u_long exp, struct LongArray *input);
struct CalculationsTable *parse_table_input(FILE *file);
u_long sum_valid_results(struct CalculationsTable *table);
struct IntMatrix *generate_combinations(int num_operations);
void decimal_to_binary_array(int decimal, int* binary_array, int size);

#endif
