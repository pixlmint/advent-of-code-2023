#ifndef AOC
#define AOC
#include <stdbool.h>
#include <stdio.h>
char *read_file(const char *fp);
void sort_integer_array(int* arr, int arr_size);

typedef struct IntArray {
    int length;
    int max_length;
    int *values;
} IntArray;

typedef struct LongArray {
    int length;
    int max_length;
    long *values;
} LongArray;

typedef struct IntMatrix {
    int **data;
    int rows;
    int cols;
} IntMatrix;

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct PointArray {
    int length;
    int max_length;
    Point **points;
} PointArray;


IntArray *init_int_array(const int max_length);
LongArray *init_long_array(const int max_length);
PointArray *init_point_array(const int max_length);


int int_array_append(IntArray *array, int value);
int long_array_append(LongArray *array, long value);
int point_array_append(PointArray *arr, Point *point);
int append_coords(PointArray *arr, int x, int y);
int int_array_index_of(IntArray *array, int search);
int long_array_index_of(LongArray *array, long search);
int point_array_index_of(PointArray *arr, Point *search);
void free_array(IntArray *array);
void free_long_array(LongArray *array);
void free_point_array(PointArray *arr);
void print_int_array(IntArray *arr);
void print_long_array(LongArray *arr);

bool is_numeric(char character);
int char_to_int(char character);

int count_lines(FILE *file);
int count_columns(FILE *file);

IntMatrix *init_int_matrix(const int rows, const int cols);
void free_matrix(IntMatrix *matrix);
IntMatrix *transpose_int_matrix(IntMatrix *original);
IntMatrix *flip_int_matrix(IntMatrix *original);
IntMatrix *clone_int_matrix(IntMatrix *original);
void print_matrix(IntMatrix *matrix);
void print_matrix_as_char(IntMatrix *matrix);
IntArray *get_diagonal_from_matrix(IntMatrix *matrix, int row, int col);

int *copy_array_section(int* source, int start, int end);

int min(int x, int y);
double pow(double base, double exponent);

#endif
