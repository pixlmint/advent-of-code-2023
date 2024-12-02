#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "day01.h"
#include "aoc.h"

int count_occurences(const int* arr, const int search, const int arr_size) {
    int occurrences = 0;
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] == search) {
            occurrences += 1;
        }
    }

    return occurrences;
}

int solve_day01(const char *input_file) {
    // printf("Input for Day 01: %s\n", input_file);
    // printf("%s\n", read_file(input_file));
    // const char *input = read_file(input_file);
    int left_numbers[1000];
    int right_numbers[1000];
    int NUMBER_LENGTH = 5;

    FILE *file = fopen(input_file, "r");
    int file_position = 1;
    char *l_num = malloc(sizeof(char) * NUMBER_LENGTH + 1);
    char *r_num = malloc(sizeof(char) * NUMBER_LENGTH + 1);
    fseek(file, 0, SEEK_SET);
    char *line = malloc(sizeof(char) * NUMBER_LENGTH * 2 + 5);
    for (int i = 0; i < 1000; i++) {
        fgets(line, NUMBER_LENGTH * 2 + 2, file);
        fseek(file, 1, SEEK_CUR);
        /*printf("Line: %s\n", line);*/
        strncpy(l_num, line, NUMBER_LENGTH);
        strncpy(r_num, line + NUMBER_LENGTH + 1, NUMBER_LENGTH);
        /*printf("Left number %s\n", l_num);*/
        /*printf("Right number %s\n", r_num);*/
        left_numbers[i] = atoi(l_num);
        right_numbers[i] = atoi(r_num);
    }
    free(l_num);
    free(r_num);
    free(line);
    sort_integer_array(left_numbers, 1000);
    sort_integer_array(right_numbers, 1000);

    // Part 1
    long sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += abs(left_numbers[i] - right_numbers[i]);
    }

    printf("Result: %ld\n", sum);

    // Part 2
    long similarity_score = 0;
    for (int i = 0; i < 1000; i++) {
        similarity_score += left_numbers[i] * count_occurences(right_numbers, left_numbers[i], 1000);
    }
    printf("Similarity Score: %ld\n", similarity_score);
    return sum;
}

