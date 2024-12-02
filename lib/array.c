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
