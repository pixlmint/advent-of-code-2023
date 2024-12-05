#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "aoc.h"
#include "day04.h"

const char* TEST_FILE = "tests/test_day04_input.txt";

FILE *open_test_file() {
    FILE *file = fopen(TEST_FILE, "r");

    if (!file) {
        return NULL;
    }

    return file;
}

static void test_create_mask_array(void **state) {
    FILE *file = open_test_file();
    assert_non_null(file);

    struct IntMatrix *mask = create_mask_array(file);
    assert_int_equal(ftell(file), 0);
    assert_non_null(mask);

    fclose(file);
    free_matrix(mask);
}

static void test_mask_input(void **state) {
    FILE *file = open_test_file();
    assert_non_null(file);

    struct IntMatrix *mask = create_mask_array(file);
    assert_non_null(mask);

    mask_input(file, mask);

    assert_int_equal(ftell(file), 0);

    fclose(file);

    assert_int_equal(mask->data[0][0], 1);
    assert_int_equal(mask->data[0][9], 2);
    assert_int_equal(mask->data[1][0], 3);
    assert_int_equal(mask->data[6][2], 1);
    assert_int_equal(mask->data[6][3], 2);
    assert_int_equal(mask->data[6][4], 3);
    assert_int_equal(mask->data[6][5], 4);

    free_matrix(mask);
}

static void test_count_lines(void **state) {
    FILE *file = open_test_file();
    assert_non_null(file);

    assert_int_equal(count_lines(file), 10);

    assert_int_equal(ftell(file), 0);

    fclose(file);
}

static void test_copy_array_section(void **state) {
    int source[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    int *copy = copy_array_section(source, 3, 5);

    assert_int_equal(copy[0], 4);
    assert_int_equal(copy[1], 5);
    assert_int_not_equal(copy[2], 6);

    free(copy);
}

static void test_count_in_row(void **state) {
    int correct[] = {0, 0, 1, 2, 3, 0, 0};
    int correct_2[] = {0, 0, 0, 0, 1, 2, 3};
    int incorrect[] = {0, 0, 1, 2, 0, 0, 0};
    int incorrect_2[] = {0, 0, 0, 0, 0, 1, 2};
    int length = 7;
    int correct_inverted[length];
    int correct_2_inverted[length];
    int incorrect_inverted[length];
    int incorrect_2_inverted[length];
    int expected_matches = 3;

    for (int i = 0; i < length; i++) {
        correct_inverted[i] = correct[length - 1 - i];
        correct_2_inverted[i] = correct_2[length - 1 - i];
        incorrect_inverted[i] = incorrect[length - 1 - i];
        incorrect_2_inverted[i] = incorrect_2[length - 1 - i];
    }

    assert_int_equal(count_in_row(correct, length, expected_matches), 1);
    assert_int_equal(count_in_row(incorrect, length, expected_matches), 0);

    assert_int_equal(count_in_row(correct_2, length, expected_matches), 1);
    assert_int_equal(count_in_row(incorrect_2, length, expected_matches), 0);

    assert_int_equal(count_in_row(correct_inverted, length, expected_matches), 1);
    assert_int_equal(count_in_row(incorrect_inverted, length, expected_matches), 0);

    assert_int_equal(count_in_row(correct_2_inverted, length, expected_matches), 1);
    assert_int_equal(count_in_row(incorrect_2_inverted, length, expected_matches), 0);
}

static void test_transpose_int_matrix(void **state) {
    struct IntMatrix *matrix = init_int_matrix(3, 4);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            matrix->data[i][j] = i;
        }
    }
    struct IntMatrix *transposed = transpose_int_matrix(matrix);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            assert_int_equal(transposed->data[i][j], j);
        }
    }

    free_matrix(matrix);
    free_matrix(transposed);
}

static void test_flip_int_matrix(void **state) {
    struct IntMatrix *matrix = init_int_matrix(3, 4);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            matrix->data[i][j] = i + j;
        }
    }
    // printf("Original:\n");
    // print_matrix(matrix);
    struct IntMatrix *flipped = flip_int_matrix(matrix);
    // printf("Transposed:\n");
    // print_matrix(flipped);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            assert_int_equal(flipped->data[i][flipped->cols - j - 1], i + j);
        }
    }

    free_matrix(matrix);
    free_matrix(flipped);
}

static void test_get_diagonal_from_matrix(void **state) {
    struct IntMatrix *matrix = init_int_matrix(4, 3);

    int row = 0;
    for (int i = 0; i < 12; i++) {
        matrix->data[row][i % 3] = i;
        if ((i + 1) % 3 == 0) {
            row++;
        } 
    }

    // print_matrix(matrix);

    struct IntArray *diag = get_diagonal_from_matrix(matrix, 0, 1);
    assert_int_equal(diag->values[0], 1);
    assert_int_equal(diag->values[1], 5);
    assert_int_equal(diag->length, 2);

    free_array(diag);

    diag = get_diagonal_from_matrix(matrix, 0, 0);
    assert_int_equal(diag->values[0], 0);
    assert_int_equal(diag->values[1], 4);
    assert_int_equal(diag->values[2], 8);
    assert_int_equal(diag->length, 3);

    free_array(diag);

    diag = get_diagonal_from_matrix(matrix, 1, 0);
    assert_int_equal(diag->values[0], 3);
    assert_int_equal(diag->values[1], 7);
    assert_int_equal(diag->values[2], 11);
    assert_int_equal(diag->length, 3);

    free_array(diag);

    struct IntMatrix *tmp = transpose_int_matrix(matrix);
    free_matrix(matrix);
    matrix = tmp;

    // print_matrix(matrix);

    diag = get_diagonal_from_matrix(matrix, 0, 1);
    assert_int_equal(diag->values[0], 3);
    assert_int_equal(diag->values[1], 7);
    assert_int_equal(diag->values[2], 11);
    assert_int_equal(diag->length, 3);

    free_array(diag);

    diag = get_diagonal_from_matrix(matrix, 1, 0);
    assert_int_equal(diag->values[0], 1);
    assert_int_equal(diag->values[1], 5);
    assert_int_equal(diag->length, 2);

    free_array(diag);

    diag = get_diagonal_from_matrix(matrix, 0, 0);
    assert_int_equal(diag->values[0], 0);
    assert_int_equal(diag->values[1], 4);
    assert_int_equal(diag->values[2], 8);
    assert_int_equal(diag->length, 3);

    free_array(diag);

    free_matrix(matrix);
}

static void test_count_total_occurrences(void **state) {
    FILE *file = fopen("tests/test_day04_input_2.txt", "r");
    struct IntMatrix *mask = create_mask_array(file);
    mask_input(file, mask);
    fclose(file);

    // printf("lines: %d, cols: %d\n", mask->rows, mask->cols);
    // print_matrix(mask);
    // printf("Transposed:\n");
    // print_matrix(transpose_int_matrix(mask));
    assert_int_equal(mask->cols, 10);
    assert_int_equal(mask->rows, 10);

    assert_int_equal(count_total_occurrences(mask), 18);
    free_matrix(mask);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_count_lines),
        cmocka_unit_test(test_create_mask_array),
        cmocka_unit_test(test_mask_input),
        cmocka_unit_test(test_copy_array_section),
        cmocka_unit_test(test_count_in_row),
        cmocka_unit_test(test_transpose_int_matrix),
        cmocka_unit_test(test_flip_int_matrix),
        cmocka_unit_test(test_get_diagonal_from_matrix),
        cmocka_unit_test(test_count_total_occurrences),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
