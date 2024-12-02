#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day01.h"
#include "aoc.h"

void test_day01() {
}

void test_file_reading() {
    char* fname = "tests/test_day01_input.txt";
    FILE *file = fopen(fname, "r");

    if (!file) {
        perror("Unable to read filename"); 
        assert(1);
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("File length: %ld\n", length);

    // fseek(file, 0, SEEK_SET);
    char *num_3 = malloc(100);
    char *num_4 = malloc(100);

    fgets(num_3, 4, file);

    // fread(num_3, 1, 1, file);
    fseek(file, 4, SEEK_SET);
    fgets(num_4, 100, file);
    printf("Read from string:\n");
    printf("%s\n", num_3);
    printf("%s\n", num_4);
    printf("num_4 length: %ld\n", strlen(num_4));
}

void test_sorting() {
    int values[] = {3, 2, 5, 8};
    sort_integer_array(values, 4);
    assert(values[0] == 2);
    assert(values[1] == 3);
    assert(values[2] == 5);
    assert(values[3] == 8);
}

int main() {
    test_day01();
    test_file_reading();
    test_sorting();
    return 0;
}
