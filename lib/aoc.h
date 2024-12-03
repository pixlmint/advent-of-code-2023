#ifndef AOC
#define AOC
#include <stdbool.h>
char *read_file(const char *fp);
void sort_integer_array(int* arr, int arr_size);

struct IntArray {
    int length;
    int max_length;
    int *values;
};

struct IntArray *init_int_array(const int max_length);

int int_array_append(struct IntArray *array, int value);
void free_array(struct IntArray *array);
bool is_numeric(char character);
int char_to_int(char character);

#endif
