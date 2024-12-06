#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "aoc.h"


char *read_file(const char *fp) {
    FILE *file = fopen(fp, "r");
    if (!file) {
        perror("Error opening input file");
        return "";
    }

    // Get length of file
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *input = malloc(length + 1);
    if (!input) {
        perror("Memory allocation failed");
        fclose(file);
        return "";
    }

    fread(input, 1, length, file);
    fclose(file);
    input[length] = '\0';

    return input;
}


bool is_numeric(char character) {
    return character > 47 && character < 58;
}

int char_to_int(char character) {
    return character - 48;
}

int count_lines(FILE *file) {
    char *line = calloc(sizeof(char), 1000);
    int lines = 0;
    // Get length of file
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    while (length > lines * strlen(line)) {
        fgets(line, 1000, file);
        lines++;
    }
    fseek(file, 0, SEEK_SET);
    free(line);

    return lines;
}

int min(int x, int y) {
    return y ^ ((x ^ y)) & -(x < y);
}

int max(int x, int y) {
    return x > y ? x : y;
}

void swap(int* arr, int i, int j) {
    int i_val = arr[i];
    arr[i] = arr[j];
    arr[j] = i_val;
}

/**
 * Basic sorting using insert sort
 * @param arr the Array to sort
 */
void sort_integer_array(int* arr, int arr_size) {
    for (int i = 1; i < arr_size; i++) {
        int i_val = arr[i];
        int j;
        for (j = i; (j > 0 && arr[j - 1] > i_val); j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = i_val;
    }
}

