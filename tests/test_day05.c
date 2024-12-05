#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "aoc.h"
#include "day05.h"

static void test_parse_ordering(void **state) {
    char *test = "33,35,46";
    struct IntArray *ordering = parse_ordering(test);
    assert_int_equal(ordering->length, 3);
    assert_int_equal(ordering->values[0], 33);
    assert_int_equal(ordering->values[1], 35);
    assert_int_equal(ordering->values[2], 46);
    free_array(ordering);
}

static void test_int_array_index_of(void **state) {
    struct IntArray *arr = init_int_array(5);

    for (int i = 0; i < 5; i++) {
        int_array_append(arr, i);
    }

    assert_int_equal(int_array_index_of(arr, 0), 0);
    assert_int_equal(int_array_index_of(arr, 1), 1);
    assert_int_equal(int_array_index_of(arr, 4), 4);
    assert_int_equal(int_array_index_of(arr, 5), -1);

    free_array(arr);
}

static void test_rulesets(void **state) {
    struct Ruleset *set = init_ruleset();
    int ret = register_page_number_rule(set, 1, 1);
    assert_int_equal(ret, -1);
    assert_int_equal(set->rule_count, 1);
    assert_int_equal(set->rules[0]->page_number, 1);
    ret = register_page_number_rule(set, 1, 2);
    assert_int_equal(ret, 0);

    free_ruleset(set);
}

static void test_parse_rule(void **state) {
    int tuple[] = {-1, -1};
    parse_rule("1|2", tuple);
    assert_int_equal(tuple[0], 1);
    assert_int_equal(tuple[1], 2);

    parse_rule("10|25", tuple);
    assert_int_equal(tuple[0], 10);
    assert_int_equal(tuple[1], 25);
}

struct Ruleset *get_parsed_ruleset() {
    char *fn = "tests/test_day05_input.txt";
    FILE *file = fopen(fn, "r");
    assert_non_null(file);

    struct Ruleset *set = parse_rules(file);
    fclose(file);
    return set;
}

static void test_parse_rules(void **state) {
    struct Ruleset *set = get_parsed_ruleset();

    assert_int_equal(set->rule_count, 6);
    assert_int_equal(set->order_count, 6);

    free_ruleset(set);
}

static void test_validate_order(void **state) {
    struct Ruleset *set = get_parsed_ruleset();

    char *res = calloc(sizeof(char), set->order_count + 1);
    for (int i = 0; i < set->order_count; i++) {
        res[i] = is_valid_order(set->orders[i], set) == 0 ? 'y' : 'n';
    }

    char *exp = "yyynnn";
    assert_string_equal(res, exp);

    free(res);
    free_ruleset(set);
}

static void test_sum_correct_orders(void **state) {
    struct Ruleset *set = get_parsed_ruleset();

    int sum = sum_correct_orders(set);

    assert_int_equal(sum, 143);

    free_ruleset(set);
}

static void test_fix_orders(void **state) {
    struct Ruleset *set = get_parsed_ruleset();

    fix_orders(set);
    int sum = sum_correct_orders(set);

    assert_int_equal(sum, 143 + 123);

    free_ruleset(set);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_parse_ordering),
        cmocka_unit_test(test_int_array_index_of),
        cmocka_unit_test(test_rulesets),
        cmocka_unit_test(test_parse_rules),
        cmocka_unit_test(test_parse_rule),
        cmocka_unit_test(test_validate_order),
        cmocka_unit_test(test_sum_correct_orders),
        cmocka_unit_test(test_fix_orders),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
