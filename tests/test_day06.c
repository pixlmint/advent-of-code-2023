#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "aoc.h"
#include "day06.h"

FILE *open_test_file() {
    FILE *file = fopen("tests/test_day06_input.txt", "r");

    if (!file) {
        perror("Unable to read test file\n");
        return NULL;
    }

    return file;
}

static void test_read_map(void **state) {
    FILE *file = open_test_file();

    struct Room *room = read_room(file);
    fclose(file);
    struct IntMatrix *map = room->map;

    assert_int_equal(map->cols, 10);
    assert_int_equal(map->rows, 10);

    assert_int_equal(map->data[room->guard_y][room->guard_x], VISITED);

    free_room(room);
}

static void test_get_next_position(void **state) {
    int pos[] = {0, 0};
    get_next_position(DIRECTION_UP, pos);
    assert_int_equal(0, pos[0]);
    assert_int_equal(-1, pos[1]);

    get_next_position(DIRECTION_DOWN, pos);
    assert_int_equal(0, pos[0]);
    assert_int_equal(0, pos[1]);

    get_next_position(DIRECTION_RIGHT, pos);
    assert_int_equal(1, pos[0]);
    assert_int_equal(0, pos[1]);

    get_next_position(DIRECTION_LEFT, pos);
    assert_int_equal(0, pos[0]);
    assert_int_equal(0, pos[1]);
}

static void test_solve(void **state) {
    FILE *file = open_test_file();
    struct Room *room = read_room(file);
    fclose(file);

    solve(room);

    print_matrix(room->map);

    assert_int_equal(room->steps, 41);

    free_room(room);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_read_map),
        cmocka_unit_test(test_solve),
        cmocka_unit_test(test_get_next_position),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
