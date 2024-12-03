#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "day03.h"
#include "aoc.h"


static void test_solve_multiplication(void **state) {
    assert_int_equal(6, solve_multiplication("mul(3,2)"));
    assert_int_equal(121, solve_multiplication("mul(11,11)"));
}

static void test_is_numeric(void **state) {
    assert_true(is_numeric('3'));
    assert_true(is_numeric('9'));
    assert_true(is_numeric(50));
    assert_false(is_numeric('/'));
    assert_false(is_numeric(60));
}

static void test_char_to_int(void **state) {
    assert_int_equal(6, char_to_int('6'));
    assert_int_equal(0, char_to_int('0'));
    assert_int_equal(0, char_to_int(48));
    assert_int_equal(9, char_to_int('9'));
    assert_int_equal(9, char_to_int(57));
}


int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_solve_multiplication),
        cmocka_unit_test(test_is_numeric),
        cmocka_unit_test(test_char_to_int),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
