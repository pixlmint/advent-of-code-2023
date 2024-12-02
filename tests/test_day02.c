#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "day02.h"
#include "aoc.h"

void test_day02() {
}

void test_read_file_linebyline() {
    char* fname = "tests/test_day02_input.txt";
    FILE *file = fopen(fname, "r");

    if (!file) {
        perror("Unable to read filename"); 
        assert(1);
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char SEPARATOR = ' ';
    int MAX_NUMBER_LENGTH = 20;
    struct IntArray *numbers = init_int_array(2);
    int next_number_index = 0;

    // words may not be longer than 20 characters
    char* current_word = calloc(MAX_NUMBER_LENGTH, sizeof(char));
    int current_word_length = 0;
    char current_char;

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
        }
    }
    fclose(file);
    free(current_word);

    assert(numbers->values[0] == 1);
    assert(numbers->values[1] == 2);
    assert(numbers->values[2] == 3);
    assert(numbers->values[3] == 4);
    assert(numbers->values[4] == 5);
    assert(numbers->values[5] == 6);
    assert(numbers->values[6] == 7);
    assert(numbers->values[7] == 81);

    free_array(numbers);
}

static void test_is_report_safe(void **state) {
    struct IntArray *test_levels = malloc(sizeof(struct IntArray));
    int unsafe_levels[] = {1, 2, 7, 8, 9};
    int safe_levels[] = {7, 6, 4, 2, 1};
    test_levels->max_length = 5;
    test_levels->length = 5;
    test_levels->values = unsafe_levels;

    assert_false(is_report_safe(test_levels, 0));

    test_levels->values = safe_levels;
    assert_true(is_report_safe(test_levels, 0));

    free(test_levels);
}

static void test_is_report_safe_with_dampeners(void **state) {
    struct IntArray *test_levels = malloc(sizeof(struct IntArray));
    int unsafe_levels[] = {1, 2, 7, 8, 9};
    int safe_levels[] = {7, 6, 4, 2, 1};
    test_levels->max_length = 5;
    test_levels->length = 5;
    test_levels->values = unsafe_levels;

    assert_false(is_report_safe(test_levels, 1));

    test_levels->values = safe_levels;
    assert_true(is_report_safe(test_levels, 1));

    free(test_levels);
}

int main() {
    test_read_file_linebyline();
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_is_report_safe),
    };
 
    return cmocka_run_group_tests(tests, NULL, NULL);
    return 0;
}
