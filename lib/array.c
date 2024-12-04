#include <math.h>
#include <stdlib.h>
#include "aoc.h"

struct IntArray *init_int_array(const int max_length) {
    struct IntArray *numbers = malloc(sizeof(struct IntArray));
    numbers->length = 0;
    numbers->max_length = max_length;
    numbers->values = malloc(sizeof(int) * max_length);

    return numbers;
}

void int_array_extend(struct IntArray *array) {
    array->max_length += array->max_length / 2;
    int* original_array = array->values;

    array->values = malloc(sizeof(int) * array->max_length);
    for (int i = 0; i < array->length; i++) {
        array->values[i] = original_array[i];
    }
    free(original_array);
}

int int_array_append(struct IntArray *array, int value) {
    if (array->length == array->max_length) {
        int_array_extend(array); 
    }
    int pos = array->length;

    array->values[pos] = value;
    array->length += 1;
    return pos;
}

void free_array(struct IntArray *array) {
    free(array->values);
    free(array);
}

int *copy_array_section(int *source, int start, int end) {
    if (start > end) {
        fprintf(stderr, "Start is bigger than end: %d > %d\n", start, end);
        return NULL;
    }
    int *copy = malloc(sizeof(int) * (end - start));
    for (int i = start; i < end; i++) {
        copy[i - start] = source[i];
    }

    return copy;
}

struct IntMatrix *init_int_matrix(const int rows, const int cols) {
    struct IntMatrix *m = malloc(sizeof(struct IntMatrix));
    m->cols = cols;
    m->rows = rows;
    m->data = malloc(rows * sizeof(int*));

    for (int i = 0; i < rows; i++) {
        m->data[i] = malloc(sizeof(int) * cols);
    }

    return m;
}

struct IntMatrix *transpose_int_matrix(struct IntMatrix *original) {
    struct IntMatrix *transposed = init_int_matrix(original->cols, original->rows);

    for (int i = 0; i < original->rows; i++) {
        for (int j = 0; j < original->cols; j++) {
            transposed->data[j][i] = original->data[i][j];
        }
    }

    return transposed;
}

struct IntMatrix *clone_int_matrix(struct IntMatrix *original) {
    struct IntMatrix *clone = init_int_matrix(original->rows, original->cols);

    for (int i = 0; i < original->rows; i++) {
        for (int j = 0; j < original->cols; j++) {
            clone->data[i][j] = original->data[i][j];
        }
    }

    return clone;
}

struct IntMatrix *flip_int_matrix(struct IntMatrix *original) {
    struct IntMatrix *flipped = init_int_matrix(original->rows, original->cols);

    for (int i = 0; i < original->rows; i++) {
        for (int j = 0; j < original->cols; j++) {
            flipped->data[i][j] = original->data[i][original->cols - j - 1];
        }
    }

    return flipped;
}

struct IntArray *get_diagonal_from_matrix(struct IntMatrix *matrix, int row, int col) {
    struct IntArray *arr = init_int_array(matrix->cols + matrix->rows);
    if (row == 0 && col == 0) {
        for (int i = col; i < min(matrix->cols, matrix->rows); i++) {
            int_array_append(arr, matrix->data[i - col][i]);
        }
    } else if (row == 0) {
        for (int i = col; i < matrix->cols; i++) {
            int_array_append(arr, matrix->data[i - col][i]);
        }
    } else if (col == 0) {
        for (int i = row; i < matrix->rows; i++) {
            int_array_append(arr, matrix->data[i][i - row]);
        }
    }

    return arr;
}

void print_matrix(struct IntMatrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        printf("| ");
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d | ", matrix->data[i][j]);
            // printf("%d", matrix->data[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(struct IntMatrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}
