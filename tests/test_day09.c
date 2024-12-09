#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>
#include "aoc.h"
#include "day09.h"

static void test_read_disc_map(void **state) {
    char *input = "2333133121414131402";

    DiscMap *map = read_disc_map(input);

    // print_disc_map(map);

    free_disc_map(map);
}

static void test_calc_checksum(void **state) {
    char *input = "0099811188827773336446555566";
    IntArray *arr = init_int_array(strlen(input));
    for (int i = 0; i < strlen(input); i++) {
        int_array_append(arr, char_to_int(input[i]));
    }

    assert_int_equal(calc_checksum(arr), 1928);

    free_array(arr);
}

static void test_shift_map(void **state) {
    char *input = "2333133121414131402";
    char *output = "0099811188827773336446555566";

    DiscMap *map = read_disc_map(input);
    IntArray *arr = shift_map(map);

    for (int i = 0; i < arr->length; i++) {
        assert_int_equal(char_to_int(output[i]), arr->values[i]);
    }

    free_array(arr);
    free_disc_map(map);
}

static void test_shift_map_defragmented(void **state) {
    char *input = "2333133121414131402";

    DiscMap *map = read_disc_map(input);
    // print_disc_map(map);
    IntArray *arr = shift_map_without_fragmentation(map);
    // print_disc_map(map);
    // print_int_array(arr);

    u_long checksum = calc_checksum(arr);
    // printf("Checksum: %ld\n", checksum);

    free_array(arr);
    free_disc_map(map);

    assert_int_equal(checksum, 2858);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_read_disc_map),
        cmocka_unit_test(test_calc_checksum),
        cmocka_unit_test(test_shift_map),
        cmocka_unit_test(test_shift_map_defragmented),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
