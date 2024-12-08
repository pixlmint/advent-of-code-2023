#include <stdlib.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <sys/types.h>
#include "aoc.h"
#include "day07.h"

static void test_parse_calculation_row(void **state) {
    struct LongArray *arr = init_long_array(5);
    u_long res = 0;
    char *calc = "190:10 19";

    parse_calculation_row(calc, &res, arr);

    assert_int_equal(res, 190);
    assert_int_equal(arr->length, 2);
    assert_int_equal(arr->values[0], 10);
    assert_int_equal(arr->values[1], 19);

    free_long_array(arr);

    struct LongArray *arr2 = init_long_array(5);
    u_long res2 = 0;
    char *calc2 = "85704856:26 3 758 2 6 6 4 6 946 3";
    parse_calculation_row(calc2, &res2, arr2);
    assert_int_equal(res2, 85704856);
    free_long_array(arr2);
}

static void test_is_valid_calculation(void **state) {
    struct LongArray *arr = init_long_array(4);
    long_array_append(arr, 5);
    long_array_append(arr, 12);
    long_array_append(arr, 77);
    long_array_append(arr, 3);

    // +*+
    int exp = 1312;
    assert_true(is_valid_calculation(exp, arr, false));
    assert_false(is_valid_calculation(exp + 1, arr, false));

    free_long_array(arr);
}

static void test_init_table(void **state) {
    struct CalculationsTable *table = init_calculations_table(10);
    assert_int_equal(table->num_calculations, 10);

    free_calculations_table(table);
}

static void test_parse_table_input(void **state) {
    FILE *file = fopen("tests/test_day07_input.txt", "r");
    if (!file) {
        perror("Unable to read input\n");
        assert_true(false);
    }
    struct CalculationsTable *table = parse_table_input(file);
    fclose(file);

    assert_int_equal(table->num_calculations, 9);

    free_calculations_table(table);
}

static void test_sum_valid_results(void **state) {
    FILE *file = fopen("tests/test_day07_input.txt", "r");
    if (!file) {
        perror("Unable to read input\n");
        assert_true(false);
    }
    struct CalculationsTable *table = parse_table_input(file);
    fclose(file);

    u_long sum = sum_valid_results(table, false);
    
    assert_int_equal(sum, 3749);

    free_calculations_table(table);
}

static void test_sum_valid_results_with_concatenation(void **state) {
    FILE *file = fopen("tests/test_day07_input.txt", "r");
    if (!file) {
        perror("Unable to read input\n");
        assert_true(false);
    }
    struct CalculationsTable *table = parse_table_input(file);
    fclose(file);

    u_long sum = sum_valid_results(table, true);
    
    assert_int_equal(sum, 11387);

    free_calculations_table(table);
}

static void test_generate_combinations(void **state) {
    struct IntMatrix *ops = generate_combinations(3, 2);
    // print_matrix(ops);
    free_matrix(ops);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init_table),
        cmocka_unit_test(test_parse_calculation_row),
        cmocka_unit_test(test_is_valid_calculation),
        cmocka_unit_test(test_sum_valid_results),
        cmocka_unit_test(test_sum_valid_results_with_concatenation),
        cmocka_unit_test(test_parse_table_input),
        cmocka_unit_test(test_generate_combinations),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
