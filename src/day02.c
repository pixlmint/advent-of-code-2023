#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "aoc.h"
#include "day02.h"


bool is_report_safe(struct IntArray *levels, int dampeners) {
    bool is_increasing = false;
    int last_number = levels->values[0];
    int problem_count = 0;
    for (int i = 1; i < levels->length; i++) {
        int current_number = levels->values[i];
        if (i == 1) {
            is_increasing = last_number < current_number;
        } else {
            if (is_increasing && last_number > current_number) {
                problem_count++;
            } else if (!is_increasing && last_number < current_number) {
                problem_count++;
            }
        }
        int diff = abs(last_number - current_number);
        if (diff < 1 || diff > 3) {
            problem_count++;
        }
        last_number = levels->values[i];
    }

    if (problem_count > 0 && dampeners > 0) {
        struct IntArray *reduced_levels = malloc(sizeof(struct IntArray));
        reduced_levels->length = levels->length - 1;
        reduced_levels->max_length = levels->length - 1;
        int reduced_arr[reduced_levels->length];
        reduced_levels->values = reduced_arr;

        for (int j = 0; j < levels->length; j++) {
            for (int i = 0; i < levels->length; i++) {
                if (i < j) {
                    reduced_levels->values[i] = levels->values[i];
                } else if (i > j) {
                    reduced_levels->values[i - 1] = levels->values[i];
                }
            }
            if (is_report_safe(reduced_levels, dampeners - 1)) {
                free(reduced_levels);
                return true;
            }
        }
        free(reduced_levels);
    }

    return problem_count == 0;
}

int solve_day02(const char *input) {
    FILE *file = fopen(input, "r");

    if (!file) {
        perror("Unable to read filename"); 
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char SEPARATOR = ' ';
    int MAX_NUMBER_LENGTH = 20;
    struct IntArray *numbers = init_int_array(10);
    int next_number_index = 0;

    // words may not be longer than 20 characters
    char* current_word = calloc(MAX_NUMBER_LENGTH, sizeof(char));
    int current_word_length = 0;
    char current_char;

    int num_safe_reports = 0;

    for (int i = 0; i < length; i++) {
        fread(&current_char, 1, 1, file);
        current_char = current_char == '\0' ? SEPARATOR : current_char;

        if (current_char != SEPARATOR && current_char != '\n') {
            strncat(current_word, &current_char, 1);
            current_word_length += 1;
        } else if (current_word_length >= MAX_NUMBER_LENGTH) {
            char* err_msg = malloc(sizeof(char) * 255);
            sprintf(err_msg, "Number exceeds maximum number of %d characters\n", MAX_NUMBER_LENGTH);
            perror(err_msg);
            free(err_msg);
        } else if (current_word_length > 0) {
            int_array_append(numbers, atoi(current_word));
            next_number_index += 1;
            current_word_length = 0;
            memset(current_word, 0, MAX_NUMBER_LENGTH);
            if (current_char == '\n') {
                if (is_report_safe(numbers, 1)) {
                    num_safe_reports++;
                }
                free_array(numbers);
                numbers = init_int_array(10);
            }
        }
    }

    fclose(file);
    free(current_word);

    free_array(numbers);

    printf("Number of safe reports: %d\n", num_safe_reports);

    return 0;
}
