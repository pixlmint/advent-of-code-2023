#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "aoc.h"
#include "day02.h"


/*
--- Day 2: Red-Nosed Reports ---

Fortunately, the first location The Historians want to search isn't a long walk
from the Chief Historian's office.

While the Red-Nosed Reindeer nuclear fusion/fission plant appears to contain no
sign of the Chief Historian, the engineers there run up to you as soon as
they see you. Apparently, they still talk about the time Rudolph was saved
through molecular synthesis from a single electron.

They're quick to add that - since you're already here - they'd really appreciate
your help analyzing some unusual data from the Red-Nosed reactor.
You turn to check if The Historians are waiting for you, but they seem to have 
already divided into groups that are currently searching every corner of
the facility. You offer to help with the unusual data.

The unusual data (your puzzle input) consists of many reports, one report per
line. Each report is a list of numbers called levels that are separated by spaces.
For example:

7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9

This example data contains six reports each containing five levels.

The engineers are trying to figure out which reports are safe.
The Red-Nosed reactor safety systems can only tolerate levels that are either
gradually increasing or gradually decreasing.
So, a report only counts as safe if both of the following are true:

    The levels are either all increasing or all decreasing.
    Any two adjacent levels differ by at least one and at most three.

In the example above, the reports can be found safe or unsafe by checking those rules:

    7 6 4 2 1: Safe because the levels are all decreasing by 1 or 2.
    1 2 7 8 9: Unsafe because 2 7 is an increase of 5.
    9 7 6 2 1: Unsafe because 6 2 is a decrease of 4.
    1 3 2 4 5: Unsafe because 1 3 is increasing but 3 2 is decreasing.
    8 6 4 4 1: Unsafe because 4 4 is neither an increase or a decrease.
    1 3 6 7 9: Safe because the levels are all increasing by 1, 2, or 3.

So, in this example, 2 reports are safe.

Analyze the unusual data from the engineers. How many reports are safe?

Your puzzle answer was 236.

The first half of this puzzle is complete! It provides one gold star: *
--- Part Two ---

The engineers are surprised by the low number of safe reports until they realize they forgot to tell you about the Problem Dampener.

The Problem Dampener is a reactor-mounted module that lets the reactor safety systems tolerate a single bad level in what would otherwise be a safe report. It's like the bad level never happened!

Now, the same rules apply as before, except if removing a single level from an unsafe report would make it safe, the report instead counts as safe.

More of the above example's reports are now safe:

    7 6 4 2 1: Safe without removing any level.
    1 2 7 8 9: Unsafe regardless of which level is removed.
    9 7 6 2 1: Unsafe regardless of which level is removed.
    1 3 2 4 5: Safe by removing the second level, 3.
    8 6 4 4 1: Safe by removing the third level, 4.
    1 3 6 7 9: Safe without removing any level.

Thanks to the Problem Dampener, 4 reports are actually safe!

Update your analysis by handling situations where the Problem Dampener can remove a single level from unsafe reports. How many reports are now safe?

Analyze the unusual data from the engineers. How many reports are safe?

Your puzzle answer was 236.

The first half of this puzzle is complete! It provides one gold star: *

--- Part Two ---

The engineers are surprised by the low number of safe reports until they realize they forgot to tell you about the Problem Dampener.

The Problem Dampener is a reactor-mounted module that lets the reactor safety systems tolerate a single bad level in what would otherwise be a safe report. It's like the bad level never happened!

Now, the same rules apply as before, except if removing a single level from an unsafe report would make it safe, the report instead counts as safe.

More of the above example's reports are now safe:

    7 6 4 2 1: Safe without removing any level.
    1 2 7 8 9: Unsafe regardless of which level is removed.
    9 7 6 2 1: Unsafe regardless of which level is removed.
    1 3 2 4 5: Safe by removing the second level, 3.
    8 6 4 4 1: Safe by removing the third level, 4.
    1 3 6 7 9: Safe without removing any level.

Thanks to the Problem Dampener, 4 reports are actually safe!

Update your analysis by handling situations where the Problem Dampener
can remove a single level from unsafe reports. How many reports are now safe?
*/


bool is_report_safe(struct IntArray *levels, int dampeners) {
    bool is_increasing = false;
    int last_number = levels->values[0];
    int problem_count = 0;
    for (int i = 1; i < levels->length; i++) {
        int current_number = levels->values[i];
        if (i == 1) {
            is_increasing = last_number < current_number;
        } else {
            if (is_increasing && last_number > current_number) {
                problem_count++;
            } else if (!is_increasing && last_number < current_number) {
                problem_count++;
            }
        }
        int diff = abs(last_number - current_number);
        if (diff < 1 || diff > 3) {
            problem_count++;
        }
        last_number = levels->values[i];
    }

    if (problem_count > 0 && dampeners > 0) {
        struct IntArray *reduced_levels = malloc(sizeof(struct IntArray));
        reduced_levels->length = levels->length - 1;
        reduced_levels->max_length = levels->length - 1;
        int reduced_arr[reduced_levels->length];
        reduced_levels->values = reduced_arr;

        for (int j = 0; j < levels->length; j++) {
            for (int i = 0; i < levels->length; i++) {
                if (i < j) {
                    reduced_levels->values[i] = levels->values[i];
                } else if (i > j) {
                    reduced_levels->values[i - 1] = levels->values[i];
                }
            }
            if (is_report_safe(reduced_levels, dampeners - 1)) {
                return true;
            }
        }
    }

    return problem_count == 0;
}

int solve_day02(const char *input) {
    FILE *file = fopen(input, "r");

    if (!file) {
        perror("Unable to read filename"); 
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char SEPARATOR = ' ';
    int MAX_NUMBER_LENGTH = 20;
    struct IntArray *numbers = init_int_array(10);
    int next_number_index = 0;

    // words may not be longer than 20 characters
    char* current_word = calloc(MAX_NUMBER_LENGTH, sizeof(char));
    int current_word_length = 0;
    char current_char;

    int num_safe_reports = 0;

    for (int i = 0; i < length; i++) {
        fread(&current_char, 1, 1, file);
        current_char = current_char == '\0' ? SEPARATOR : current_char;

        if (current_char != SEPARATOR && current_char != '\n') {
            strncat(current_word, &current_char, 1);
            current_word_length += 1;
        } else if (current_word_length >= MAX_NUMBER_LENGTH) {
            char* err_msg = malloc(sizeof(char) * 255);
            sprintf(err_msg, "Number exceeds maximum number of %d characters\n", MAX_NUMBER_LENGTH);
            perror(err_msg);
            free(err_msg);
        } else if (current_word_length > 0) {
            int_array_append(numbers, atoi(current_word));
            next_number_index += 1;
            current_word_length = 0;
            memset(current_word, 0, MAX_NUMBER_LENGTH);
            if (current_char == '\n') {
                if (is_report_safe(numbers, 1)) {
                    num_safe_reports++;
                }
                free_array(numbers);
                numbers = init_int_array(10);
            }
        }
    }

    fclose(file);
    free(current_word);

    free_array(numbers);

    printf("Number of safe reports: %d\n", num_safe_reports);

    return 0;
}
