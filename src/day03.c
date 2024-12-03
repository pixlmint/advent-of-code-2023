#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "day03.h"
#include "aoc.h"

int solve_multiplication(char *multiplication) {
    // Example multiplication: "mul(3,2)"
    int length = strlen(multiplication);

    // Numbers with more than 10 characters are not supported
    char *current_number_str = calloc(10, sizeof(char));
    bool found_comma = false;
    int current_number_length = 0;
    int first_number;
    int second_number;
    for (int i = 4; i < length - 1; i++) {
        char cur = multiplication[i];
        if (cur == ',') {
            first_number = atoi(current_number_str);
            found_comma = true;
            memset(current_number_str, 0, 10);
            current_number_length = 0;
        } else if (is_numeric(cur)) {
            current_number_str[current_number_length] = cur;
            current_number_length++;
        } else {
            perror("\nFound something that isn't numeric\n");
        }
    }
    second_number = atoi(current_number_str);
    free(current_number_str);

    return first_number * second_number;
}

int solve_day03(const char *input_path) {
    const char* input = read_file(input_path);

    // https://www.gnu.org/software/libc/manual/html_node/Regular-Expressions.html
    // http://www.mario-konrad.ch/blog/programming/regular_expressions_in_c.html
    int input_length = strlen(input);
    regex_t regex;
    regex_t regex_dont;
    regex_t regex_do;
    regmatch_t mul_pos;
    regmatch_t dont_pos;
    int error;
    int absolute = 0;
    int num_matches = 0;
    long result = 0;
    bool do_is_active = true;
    int next_dont = -1;

    char *multiplication = calloc(100, sizeof(char));

    int comp_errs[3];
    comp_errs[0] = regcomp(&regex_dont, "don't\\(\\)", REG_EXTENDED);
    comp_errs[1] = regcomp(&regex_do, "do\\(\\)", REG_EXTENDED);
    comp_errs[2] = regcomp(&regex, "mul\\([[:digit:]]+\\,[[:digit:]]+\\)", REG_EXTENDED);

    if (comp_errs[0] != 0 || comp_errs[1] != 0 || comp_errs[2] != 0) {
        perror("Unable to compile a regex\n");
        return -1;
    }

    error = regexec(&regex, input, 1, &mul_pos, 0);
    if (regexec(&regex_dont, input, 1, &dont_pos, 0) == 0) {
        next_dont = dont_pos.rm_so;
    } else {
        perror("Error executing regex_dont\n");
    }

    if (error == REG_NOMATCH) {
        printf("No matches\n");
    }

    while (error == 0 && absolute + mul_pos.rm_so < input_length) {
        int match_start = absolute + mul_pos.rm_so;
        int match_end = absolute + mul_pos.rm_eo;
        for (int i = match_start; i < match_end; i++) multiplication[i - match_start] = input[i];

        result += solve_multiplication(multiplication);

        memset(multiplication, 0, 100);
        num_matches++;
        absolute += mul_pos.rm_eo;
        error = regexec(&regex, absolute + input, 1, &mul_pos, REG_NOTBOL); 

        if (next_dont < absolute + mul_pos.rm_so) {
            absolute = next_dont;
            int dont_error = regexec(&regex_do, absolute + input, 1, &dont_pos, REG_NOTBOL);
            if (dont_error == 0) {
                absolute += dont_pos.rm_eo;
                error = regexec(&regex, absolute + input, 1, &mul_pos, REG_NOTBOL); 
                if (regexec(&regex_dont, absolute + input, 1, &dont_pos, REG_NOTBOL) == 0) {
                    next_dont = absolute + dont_pos.rm_so;
                }
            } else if (dont_error == REG_NOMATCH) {
                // No more do() calls, stop while()
                error = 1;
            }
        }

        if (num_matches > 500) {
            perror("Probably in an endless loop, exiting\n");
            error = 1;
        }
    }
    printf("num_matches: %d\n", num_matches);
    printf("Result: %ld\n", result);

    regfree(&regex);


    return 0;
}
