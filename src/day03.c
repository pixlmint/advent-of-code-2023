#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "day03.h"
#include "aoc.h"


// Resources:
ttps://www.gnu.org/software/libc/manual/html_node/Regular-Expressions.html
ttp://www.mario-konrad.ch/blog/programming/regular_expressions_in_c.html

/*
--- Day 3: Mull It Over ---

"Our computers are having issues, so I have no idea if we have any
Chief Historians in stock! You're welcome to check the warehouse, though,"
says the mildly flustered shopkeeper at the North Pole Toboggan Rental Shop.
The Historians head out to take a look.

The shopkeeper turns to you.
"Any chance you can see why our computers are having issues again?"

The computer appears to be trying to run a program,
but its memory (your puzzle input) is corrupted.
All of the instructions have been jumbled up!

It seems like the goal of the program is just to multiply some numbers.
It does that with instructions like mul(X,Y), where X and Y are each
1-3 digit numbers. For instance, mul(44,46) multiplies 44 by 46 to get a
result of 2024. Similarly, mul(123,4) would multiply 123 by 4.

However, because the program's memory has been corrupted, there are also many
invalid characters that should be ignored, even if they look like part of a
mul instruction. Sequences like mul(4*, mul(6,9!, ?(12,34),
or mul ( 2 , 4 ) do nothing.

For example, consider the following section of corrupted memory:

xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))

Only the four highlighted sections are real mul instructions.
Adding up the result of each instruction produces 161 (2*4 + 5*5 + 11*8 + 8*5).

Scan the corrupted memory for uncorrupted mul instructions.
What do you get if you add up all of the results of the multiplications?

Your puzzle answer was 169021493.
--- Part Two ---

As you scan through the corrupted memory, you notice that some of the
conditional statements are also still intact. If you handle some of the
uncorrupted conditional statements in the program,
you might be able to get an even more accurate result.

There are two new instructions you'll need to handle:

    The do() instruction enables future mul instructions.
    The don't() instruction disables future mul instructions.

Only the most recent do() or don't() instruction applies. At the beginning
of the program, mul instructions are enabled.

For example:

xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))

This corrupted memory is similar to the example from before,
but this time the mul(5,5) and mul(11,8) instructions are disabled
because there is a don't() instruction before them. The other mul instructions
function normally, including the one at the end that gets re-enabled
by a do() instruction.

This time, the sum of the results is 48 (2*4 + 8*5).

Handle the new instructions; what do you get if you add up all of the
results of just the enabled multiplications?

Your puzzle answer was 111762583.
*/

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
