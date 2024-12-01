#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>
#include <stdio.h>

#define TEST_ASSERT_EQUAL_INT(expected, actual) \
    assert_int_equal(actual, expected);

#define TEST_ASSERT_EQUAL_STRING(expected, actual) \
    assert_string_equal(actual, expected);

#define TEST_ASSERT_NULL(ptr) \
    assert_null(ptr);

#define TEST_ASSERT_NOT_NULL(ptr) \
    assert_non_null(ptr);

#endif // FRAMEWORK_H
