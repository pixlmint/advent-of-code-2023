#ifndef AOC
#define AOC
#include <stdbool.h>
#include <stdio.h>


// ------------- Int Array ----------------------------------------
typedef struct IntArray {
    int length;
    int max_length;
    int *values;
} IntArray;

void sort_integer_array(int* arr, int arr_size);
IntArray *init_int_array(const int max_length);
int int_array_append(IntArray *array, int value);
int int_array_index_of(IntArray *array, int search);
void free_array(IntArray *array);
void print_int_array(IntArray *arr);
int *copy_array_section(int* source, int start, int end);

// ------------- Long Array ---------------------------------------
typedef struct LongArray {
    int length;
    int max_length;
    long *values;
} LongArray;
LongArray *init_long_array(const int max_length);
int long_array_append(LongArray *array, long value);
int long_array_index_of(LongArray *array, long search);
void free_long_array(LongArray *array);
void print_long_array(LongArray *arr);

// ------------- Int Matrix ---------------------------------------
typedef struct IntMatrix {
    int **data;
    int rows;
    int cols;
} IntMatrix;

IntMatrix *init_int_matrix(const int rows, const int cols);
void free_matrix(IntMatrix *matrix);
IntMatrix *transpose_int_matrix(IntMatrix *original);
IntMatrix *flip_int_matrix(IntMatrix *original);
IntMatrix *clone_int_matrix(IntMatrix *original);
void print_matrix(IntMatrix *matrix);
void print_matrix_as_char(IntMatrix *matrix);
IntArray *get_diagonal_from_matrix(IntMatrix *matrix, int row, int col);

// ------------- Points ------------------------------------------
typedef struct Point {
    double x;
    double y;
} Point;

typedef struct PointArray {
    int length;
    int max_length;
    Point **points;
} PointArray;

PointArray *init_point_array(const int max_length);
int point_array_append(PointArray *arr, Point *point);
int append_coords(PointArray *arr, double x, double y);
int point_array_index_of(PointArray *arr, Point *search);
void free_point_array(PointArray *arr);
PointArray *point_array_merge(PointArray *a, PointArray *b);


// ------------- File Handling ----------------------------------
char *read_file(const char *fp);
int count_lines(FILE *file);
int count_columns(FILE *file);


// ------------- Other -----------------------------------------
int min(int x, int y);
double pow(double base, double exponent);
int gcd(int a, int b);

bool is_numeric(char character);
int char_to_int(char character);

#endif
