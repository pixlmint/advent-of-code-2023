#include <stdio.h>
#include <stdlib.h>
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

void swap(int* arr, int i, int j) {
    int i_val = arr[i];
    arr[i] = arr[j];
    arr[j] = i_val;
}

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

/*char *read_file_as_lines(const char *fp) {*/
/*    FILE *file = fopen(fp, "r");*/
/*    if (!file) {*/
/*        perror("Error opening input file");*/
/*        return "";*/
/*    }*/
/**/
/*    // Get length of file*/
/*    fseek(file, 0, SEEK_END);*/
/*    long length = ftell(file);*/
/*    fseek(file, 0, SEEK_SET);*/
/**/
/*    char *cur_line = "";*/
/*    for (int i = 0; i < length; i++) {*/
/*        char *val = malloc(1);*/
/*        fread(val, 1, 1, file);*/
/**/
/*        if (*val != '\n') {*/
/**/
/*        } else {*/
/**/
/*        }*/
/*    }*/
/*}*/

/*char *parse_csv(const char *csv_string) {*/
/*    char lines[2];*/
/*}*/
