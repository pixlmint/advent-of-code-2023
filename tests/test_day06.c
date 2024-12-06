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

    int loops = solve(room);

    assert_int_equal(room->steps, 41);
    assert_int_equal(loops, 0);

    free_room(room);
}

static void test_loop_detection(void **state) {
    FILE *file = fopen("tests/test_day06_input_loop.txt", "r");

    struct Room *room = read_room(file);
    fclose(file);

    int loops = solve(room);
    assert_int_equal(loops, 1);

    free_room(room);
}

static void test_count_possible_obstacle_placements(void **state) {
    FILE *file = open_test_file();
    struct Room *room = read_room(file);
    fclose(file);

    int obs_count = count_possible_obstacle_placements(room);

    assert_int_equal(obs_count, 6);
    
    free_room(room);
}

static void test_clone_int_matrix(void **state) {
    struct IntMatrix *matrix = init_int_matrix(5, 5);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            matrix->data[i][j] = 0;
        }
    }

    struct IntMatrix *clone = clone_int_matrix(matrix);
    matrix->data[0][0] = 1;

    assert_int_equal(clone->rows, matrix->rows);
    assert_int_equal(clone->cols, matrix->cols);

    for (int i = 0; i < clone->rows; i++) {
        for (int j = 0; j < clone->cols; j++) {
            assert_int_equal(clone->data[i][j], 0);
        }
    }

    free_matrix(clone);
    free_matrix(matrix);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_read_map),
        cmocka_unit_test(test_solve),
        cmocka_unit_test(test_get_next_position),
        cmocka_unit_test(test_loop_detection),
        cmocka_unit_test(test_count_possible_obstacle_placements),
        cmocka_unit_test(test_clone_int_matrix),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
