#include <math.h>
#include <stdlib.h>
#include "aoc.h"

// ------------- Int Array ----------------------------------------
struct IntArray *init_int_array(const int max_length) {
    struct IntArray *numbers = malloc(sizeof(struct IntArray));
    numbers->length = 0;
    numbers->max_length = max_length;
    numbers->values = malloc(sizeof(int) * max_length);

    return numbers;
}

void int_array_extend(struct IntArray *array) {
    array->max_length += array->max_length / 2;
    array->values = realloc(array->values, sizeof(int) * array->max_length);
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

int int_array_index_of(struct IntArray *array, int search) {
    for (int i = 0; i < array->length; i++) {
        if (array->values[i] == search) {
            return i;
        }
    }

    return -1;
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

void print_int_array(struct IntArray *arr) {
    printf("IntArray (length %d): [", arr->length);
    for (int i = 0; i < arr->length; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%d", arr->values[i]);
    }
    printf("]\n");
}

// ------------- Long Array ----------------------------------------
struct LongArray *init_long_array(const int max_length) {
    struct LongArray *numbers = malloc(sizeof(struct LongArray));
    numbers->length = 0;
    numbers->max_length = max_length;
    numbers->values = malloc(sizeof(long) * max_length);

    return numbers;
}

void long_array_extend(struct LongArray *array) {
    array->max_length += array->max_length / 2;
    array->values = realloc(array->values, sizeof(long) * array->max_length);
}

int long_array_append(struct LongArray *array, long value) {
    if (array->length == array->max_length) {
        long_array_extend(array); 
    }
    int pos = array->length;

    array->values[pos] = value;
    array->length += 1;
    return pos;
}

int long_array_index_of(struct LongArray *array, long search) {
    for (int i = 0; i < array->length; i++) {
        if (array->values[i] == search) {
            return i;
        }
    }

    return -1;
}

void free_long_array(struct LongArray *array) {
    free(array->values);
    free(array);
}

void print_long_array(struct LongArray *arr) {
    printf("LongArray (length %d): [", arr->length);
    for (int i = 0; i < arr->length; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%ld", arr->values[i]);
    }
    printf("]\n");
}

// ------------- Int Matrices ----------------------------------------

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
