#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "aoc.h"
#include "day07.h"

struct CalculationsTable *init_calculations_table(int num_calculations) {
    struct CalculationsTable *table = malloc(sizeof(struct CalculationsTable));
    table->num_calculations = num_calculations;
    table->results = malloc(sizeof(u_long) * num_calculations);
    table->inputs = malloc(sizeof(struct LongArray*) * num_calculations);
    for (int i = 0; i < num_calculations; i++) {
        table->results[i] = 0;
        table->inputs[i] = init_long_array(20);
    }

    return table;
}

void free_calculations_table(struct CalculationsTable *table) {
    free(table->results);
    for (int i = 0; i < table->num_calculations; i++) {
        free_long_array(table->inputs[i]);
    }
    free(table->inputs);
    free(table);
}

struct IntMatrix *generate_combinations(int num_operations, int base) {
    int combinations = pow(base, num_operations);
    struct IntMatrix *ops = init_int_matrix(combinations, num_operations);

    for (int i = 0; i < combinations; i++) {
        decimal_to_base_n_array(i, base, ops->data[i], ops->cols);
    }

    return ops;
}

void decimal_to_base_n_array(int decimal, int base, int* base_n_array, int size) {
    // Initialize array with zeros
    for (int i = 0; i < size; i++) {
        base_n_array[i] = 0;
    }
    
    // Handle special case for 0
    if (decimal == 0) {
        return;
    }
    
    // Convert decimal to base n
    int index = size - 1;
    while (decimal > 0 && index >= 0) {
        base_n_array[index] = decimal % base;
        decimal = decimal / base;
        index--;
    }
}

bool is_valid_calculation(u_long exp, struct LongArray *input, bool with_concatenation) {
    struct IntMatrix *ops;
    if (with_concatenation) {
        ops = generate_combinations(input->length - 1, 3);
    } else {
        ops = generate_combinations(input->length - 1, 2);
    }
    // print_matrix(ops);

    for (int i = 0; i < ops->rows; i++) {
        // printf("--%d---\n", i);
        u_long res = (u_long) input->values[0];
        for (int x = 0; x < ops->cols; x++) {
            // printf("%d / %d : ", x, ops->cols);
            if (ops->data[i][x] == 0) {
                // printf("%ld + %d = ", res, input->values[x + 1]);
                res += input->values[x + 1];
            } else if (ops->data[i][x] == 1) {
                // printf("%ld * %d = ", res, input->values[x + 1]);
                res *= input->values[x + 1];
            } else {
                char *str_res = malloc(sizeof(char) * 20);
                sprintf(str_res, "%ld%ld", res, input->values[x + 1]);
                res = atol(str_res);
                free(str_res);
            }
            // printf("%ld", res);

            if (res > exp) {
                // printf(" (b) \n");
                break;
            }
            // printf("\n");
        }
        // printf("%ld\n", res);
        if (res == exp) {
            free_matrix(ops);
            return true;
        }
    }
    free_matrix(ops);

    return false;
}

void parse_calculation_row(char *calc, u_long *result, struct LongArray *input) {
    int pos = 0;
    int cur_pos = 0;
    char *cur = calloc(20, sizeof(char));
    while (calc[pos] != '\0' && calc[pos] != '\n') {
        if (calc[pos] == ' ') {
            long_array_append(input, atoi(cur));
            memset(cur, 0, 20);
            cur_pos = 0;
        } else if (calc[pos] == ':') {
            *result = atol(cur);
            memset(cur, 0, 20);
            cur_pos = 0;
        } else if (is_numeric(calc[pos])) {
            cur[cur_pos] = calc[pos];
            cur_pos++;
        } else {
            fprintf(stderr, "Unknown character: '%c'\n", calc[pos]);
        }
        pos++;
    }

    long_array_append(input, atoi(cur));

    free(cur);
}

struct CalculationsTable *parse_table_input(FILE *file) {
    fseek(file, 0, SEEK_SET);
    int num_calcs = count_lines(file);
    // printf("Num calcs: %d\n", num_calcs);
    struct CalculationsTable *table = init_calculations_table(num_calcs);

    char *line = calloc(1000, sizeof(char));
    for (int i = 0; i < num_calcs; i++) {
        u_long res = 0;
        fgets(line, 1000, file);
        parse_calculation_row(line, &res, table->inputs[i]);
        table->results[i] = res;
        memset(line, 0, 1000);
    }

    free(line);

    return table;
}

u_long sum_valid_results(struct CalculationsTable *table, bool with_concatenation) {
    u_long sum = 0;
    for (int i = 0; i < table->num_calculations; i++) {
        if (is_valid_calculation(table->results[i], table->inputs[i], with_concatenation)) {
            sum += table->results[i];
        }
    }

    return sum;
}

int solve_day07(const char *input) {
    // TODO: Make sure we can work with really big numbers
    FILE *file = fopen(input, "r");
    struct CalculationsTable *table = parse_table_input(file);
    fclose(file);
    long sum = sum_valid_results(table, false);

    printf("Result: %ld\n", sum);

    long sum_concat = sum_valid_results(table, true);
    printf("Result (with concatenation): %ld\n", sum_concat);

    free_calculations_table(table);
    return 0;
}
