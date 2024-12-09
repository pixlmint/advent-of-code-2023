#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "aoc.h"
#include "day08.h"

FILE *create_dummy_file(int num_characters) {
    char *fname = malloc(sizeof(char) * 255);
    sprintf(fname, "tests/test_day08_dummy_%d.txt", num_characters);

    if (access(fname, F_OK)) {
        remove(fname);
    }

    FILE *file = fopen(fname, "w+");

    char *line = malloc(sizeof(char) * num_characters + 1);
    for (int i = 0; i < num_characters; i++) {
        line[i] = '1';
    }
    fwrite(line, sizeof(char), num_characters, file);
    free(line);
    free(fname);
    fseek(file, 0, SEEK_SET);

    return file;
}

static void test_count_columns(void **state) {
    FILE *file = create_dummy_file(20);
    int count = count_columns(file);
    assert_int_equal(count, 20);
    assert_int_equal(ftell(file), 0);
    fclose(file);

    file = create_dummy_file(1000);
    count = count_columns(file);
    assert_int_equal(count, 1000);
    assert_int_equal(ftell(file), 0);
    fclose(file);

    file = create_dummy_file(2222);
    count = count_columns(file);
    assert_int_equal(count, 2222);
    assert_int_equal(ftell(file), 0);
    fclose(file);
}

static void test_read_map(void **state) {
    FILE *file = fopen("tests/test_day08_input.txt", "r");

    AntennaTypeArray *map = read_map(file);

    fclose(file);
    free_antenna_type_array(map);
}

static void test_count_antinodes(void **state) {
    FILE *file = fopen("tests/test_day08_input.txt", "r");

    AntennaTypeArray *map = read_map(file);

    count_antinodes(map);

    assert_int_equal(map->part1_antinodes->length, 14);
    assert_int_equal(map->part2_antinodes->length, 34);

    fclose(file);
    free_antenna_type_array(map);
}

static void test_gcd(void **state) {
    assert_int_equal(gcd(4, 6), 2);
    assert_int_equal(gcd(14, 42), 14);
    assert_int_equal(gcd(16, 60), 4);
    assert_int_equal(gcd(3, -1), 1);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_count_columns),
        cmocka_unit_test(test_read_map),
        cmocka_unit_test(test_count_antinodes),
        cmocka_unit_test(test_gcd),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
