#ifndef AOC
#define AOC
#include <stdbool.h>
#include <stdio.h>
char *read_file(const char *fp);
void sort_integer_array(int* arr, int arr_size);

struct IntArray {
    int length;
    int max_length;
    int *values;
};

struct LongArray {
    int length;
    int max_length;
    long *values;
};

struct IntMatrix {
    int **data;
    int rows;
    int cols;
};


struct IntArray *init_int_array(const int max_length);
struct LongArray *init_long_array(const int max_length);

int int_array_append(struct IntArray *array, int value);
int long_array_append(struct LongArray *array, long value);
int int_array_index_of(struct IntArray *array, int search);
int long_array_index_of(struct LongArray *array, long search);
void free_array(struct IntArray *array);
void free_long_array(struct LongArray *array);
void print_int_array(struct IntArray *arr);
void print_long_array(struct LongArray *arr);

bool is_numeric(char character);
int char_to_int(char character);

int count_lines(FILE *file);

struct IntMatrix *init_int_matrix(const int rows, const int cols);
void free_matrix(struct IntMatrix *matrix);
struct IntMatrix *transpose_int_matrix(struct IntMatrix *original);
struct IntMatrix *flip_int_matrix(struct IntMatrix *original);
struct IntMatrix *clone_int_matrix(struct IntMatrix *original);
void print_matrix(struct IntMatrix *matrix);
struct IntArray *get_diagonal_from_matrix(struct IntMatrix *matrix, int row, int col);

int *copy_array_section(int* source, int start, int end);

int min(int x, int y);
double pow(double base, double exponent);

#endif
