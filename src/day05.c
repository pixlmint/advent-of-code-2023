#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "day05.h"
#include "aoc.h"

void free_ruleset(struct Ruleset *set) {
    for (int i = 0; i < set->rule_count; i++) {
        free_array(set->rules[i]->following);
        free(set->rules[i]);
    }
    free(set->rules);
    for (int i = 0; i < set->order_count; i++) {
        free_array(set->orders[i]);
    }
    free(set->orders);
    free(set);
}

struct PageNumberRules *init_page_number_rules(int number) {
    struct PageNumberRules *set = malloc(sizeof(struct PageNumberRules));
    set->page_number = number;
    set->following = init_int_array(10);
    return set;
}

struct Ruleset *init_ruleset() {
    struct Ruleset *set = malloc(sizeof(struct Ruleset));
    set->rule_count = 0;
    set->order_count = 0;
    set->rules = malloc(sizeof(struct PageNumberRules) * MAX_RULES);
    set->orders = malloc(sizeof(struct IntArray) * MAX_ORDERS);
    return set;
}

int register_page_number_rule(struct Ruleset *set, int page_number, int followed_by_number) {
    for (int i = 0; i < set->rule_count; i++) {
        if (set->rules[i]->page_number == page_number) {
            int_array_append(set->rules[i]->following, followed_by_number);
            return i;
        }
    }
    struct PageNumberRules *rules = init_page_number_rules(page_number);
    int_array_append(rules->following, followed_by_number);
    set->rules[set->rule_count++] = rules;

    return -1;
}

void parse_rule(char *rule, int *tuple) {
    char cur;
    int i = 0;
    int j = 0;
    char *number = calloc(sizeof(char), 10);
    while ((cur = rule[i++]) != '\0') {
        if (cur == '|') {
            tuple[0] = atoi(number);
            j = 0;
            memset(number, 0, 10);
        } else {
            number[j++] = cur;
        }
    }
    tuple[1] = atoi(number);
    free(number);
}

int is_valid_order(struct IntArray *order, struct Ruleset *set) {
    for (int i = order->length - 1; i >= 0; i--) {
        int val = order->values[i];
        struct PageNumberRules *appliccable_rule = NULL;
        int j = set->rule_count - 1;
        while (val != set->rules[j--]->page_number && j >= 0) {
            appliccable_rule = set->rules[j];
        }
        if (appliccable_rule != NULL && appliccable_rule->page_number == val) {
            for (int x = i - 1; x >= 0; x--) {
                int arr_index = int_array_index_of(appliccable_rule->following, order->values[x]);
                if (arr_index != -1) {
                    return appliccable_rule->following->values[arr_index];
                }
            }
        }
    }
    return 0;
}

int sum_correct_orders(struct Ruleset *set) {
    int sum = 0;
    for (int i = 0; i < set->order_count; i++) {
        struct IntArray *ord = set->orders[i];
        if (is_valid_order(ord, set) == 0) {
            int middle_index = ord->length / 2;
            sum += ord->values[middle_index];
        }
    }

    return sum;
}

struct Ruleset *parse_rules(FILE *file) {
    struct Ruleset *set = init_ruleset();

    uint step = 1;
    char line[MAX_LINE_LENGTH];
    int tmp_rule_tuple[2];
    while (fgets(line, sizeof(line), file) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        if (len == 0) {
            step++;
        } else if (step == 1) {
            parse_rule(line, tmp_rule_tuple);
            register_page_number_rule(set, tmp_rule_tuple[0], tmp_rule_tuple[1]);
        } else if (step == 2) {
            struct IntArray *order = parse_ordering(line);
            set->orders[set->order_count++] = order;
        } else {
            fprintf(stderr, "Don't know what to do with line <%s>\n", line); 
        }
    }

    return set;
}

void fix_orders(struct Ruleset *set) {
    for (int i = 0; i < set->order_count; i++) {
        struct IntArray *order = set->orders[i];
        int conflict;
        int iters = 0;
        while ((conflict = is_valid_order(order, set)) != 0) {
            for (int j = 0; j < set->rule_count; j++) {
                int conflicting_index = int_array_index_of(order, set->rules[j]->page_number);
                int tmp_conflict = int_array_index_of(set->rules[j]->following, conflict);
                if (conflicting_index != -1) {
                    for (int x = 0; x < set->rules[j]->following->length; x++) {
                        int potential_rule_conflict = int_array_index_of(order, set->rules[j]->following->values[x]);
                        if (potential_rule_conflict != -1 && potential_rule_conflict < conflicting_index) {
                            int tmp = order->values[potential_rule_conflict];
                            order->values[potential_rule_conflict] = order->values[conflicting_index];
                            order->values[conflicting_index] = tmp;
                            break;
                        }
                    }
                }
            }
            if (iters > 50) {
                fprintf(stderr, "i = %d, conflict = %d, possible endless iteration, exiting\n", i, conflict);
                break;
            }
            iters++;
        }
    }
}

bool is_break_condition(char character) {
    return character == EOF || character == '\n' || character == '\0';
}

struct IntArray *parse_ordering(char *ordering) {
    struct IntArray *order = init_int_array(strlen(ordering) / 2);
    char cur_char;
    int char_index = 0;
    char *current_number = calloc(10, sizeof(char));
    int current_number_length = 0;
    do {
        cur_char = ordering[char_index];
        if (cur_char == ',' || is_break_condition(cur_char)) {
            int_array_append(order, atoi(current_number));
            memset(current_number, 0, 10);
            current_number_length = 0;
        } else {
            current_number[current_number_length++] = cur_char;
        }
        char_index++;
    } while (!is_break_condition(cur_char));
    free(current_number);

    return order;
}


int solve_day05(const char *input) {
    FILE *file = fopen(input, "r");
    struct Ruleset *set = parse_rules(file);
    fclose(file);
    int problematic_sum = sum_correct_orders(set);
    printf("Result: %d\n", problematic_sum);

    fix_orders(set);
    int complete_sum = sum_correct_orders(set);
    printf("Result: %d\n", complete_sum - problematic_sum);
    free_ruleset(set);
    return 0;
}
