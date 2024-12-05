#include <stdio.h>
#ifndef DAY05_CONSTS
#define DAY05_CONSTS
#define MAX_RULES 200
#define MAX_LINE_LENGTH 100
#define MAX_ORDERS 200
#endif
#ifndef DAY05_H
#define DAY05_H

#include "aoc.h"
int solve_day05(const char *input);

struct PageNumberRules {
    struct IntArray *following;
    int page_number;
};

struct Ruleset {
    int rule_count;
    int order_count;
    struct PageNumberRules **rules;
    struct IntArray **orders;
};

struct PageNumberRules *init_page_number_rules(int number);
struct Ruleset *init_ruleset();
struct Ruleset *parse_rules(FILE *file);
void parse_rule(char *rule, int *tuple);
struct IntArray *parse_ordering(char *ordering);
void free_ruleset(struct Ruleset *set);
int register_page_number_rule(struct Ruleset *set, int page_number, int followed_by_number);
int is_valid_order(struct IntArray *order, struct Ruleset *set);
int sum_correct_orders(struct Ruleset *set);
void fix_orders(struct Ruleset *set);

#endif
