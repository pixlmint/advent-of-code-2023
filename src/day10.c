#include <stdio.h>
#include <stdlib.h>
#include "aoc.h"
#include "day10.h"

void print_path_matrix(PathMatrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            if (j != 0) {
                printf("| ");
            }
            printf("%d", mat->nodes[i][j]->value);
        }
        printf("\n");
    }
}

int node_list_index_of(NodeList *nodes, PathNode *search) {
    for (int i = 0; i < nodes->length; i++) {
        if (nodes->nodes[i] == search) {
            return i;
        }
    }

    return -1;
}

PathNode *create_node(int value) {
    PathNode *node = malloc(sizeof(PathNode));
    node->value = value;
    node->reached_count = 0;
    node->bot = NULL;
    node->top = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

PathMatrix *read_map(FILE *file) {
    int rows = count_lines(file);
    int cols = count_columns(file);

    // IntMatrix *map = init_int_matrix(rows, cols);
    PathMatrix *p_map = init_path_matrix(rows, cols);
    char *line = malloc(sizeof(char) * cols + 2);

    for (int i = 0; i < rows; i++) {
        fgets(line, cols + 2, file);
        for (int j = 0; j < cols; j++) {
            // map->data[i][j] = char_to_int(line[j]);
            PathNode *node = create_node(char_to_int(line[j]));
            p_map->nodes[i][j] = node;
        }
    }

    return p_map;
}

PathMatrix *init_path_matrix(int rows, int cols) {
    PathMatrix *matrix = malloc(sizeof(PathMatrix));
    matrix->cols = cols;
    matrix->rows = rows;
    matrix->nodes = malloc(rows * sizeof(int*));

    for (int i = 0; i < rows; i++) {
        matrix->nodes[i] = malloc(sizeof(PathNode) * cols);
    }

    return matrix;
}

void append_node(NodeList *list, PathNode *node) {
    if (list->max_length <= list->length) {
        list->max_length += list->max_length / 2;
        list->nodes = realloc(list->nodes, sizeof(PathNode) * list->max_length);
    }
    list->nodes[list->length++] = node;
}

NodeList *init_node_list(int length) {
    NodeList *list = malloc(sizeof(NodeList));
    list->nodes = malloc(sizeof(PathNode) * length);
    list->max_length = length;
    list->length = 0;
    return list;
}

void free_path_matrix(PathMatrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            free(mat->nodes[i][j]);
        }
        free(mat->nodes[i]);
    }
    free(mat->nodes);
    free(mat);
}

NodeList **get_nodes(PathMatrix *map) {
    NodeList *start_nodes = init_node_list(10);
    NodeList *end_nodes = init_node_list(10);
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            PathNode *cur = map->nodes[i][j];
            if (cur->value == 0) {
                append_node(start_nodes, cur);
            } else if (cur->value == 9) {
                append_node(end_nodes, cur);
            }
            if (i > 0) {
                PathNode *top = map->nodes[i - 1][j];
                if (top->value - 1 == cur->value) {
                    cur->top = top;
                }
            }
            if (i < map->rows - 1) {
                PathNode *bot = map->nodes[i + 1][j];
                if (bot->value - 1 == cur->value) {
                    cur->bot = bot;
                }
            }
            if (j > 0) {
                PathNode *left = map->nodes[i][j - 1];
                if (left->value - 1 == cur->value) {
                    cur->left = left;
                }
            }
            if (j < map->cols - 1) {
                PathNode *right = map->nodes[i][j + 1];
                if (right->value -1 == cur->value) {
                    cur->right = right;
                }
            }
        }
    }

    NodeList **ret = malloc(sizeof(int*) * 2);
    ret[0] = start_nodes;
    ret[1] = end_nodes;

    return ret;
}

void get_paths(PathNode *from, NodeList *targets) {
    if (from->value == 9) {
        // if (node_list_index_of(targets, from) == -1) {
            append_node(targets, from);
        // }
    }
    if (from->left != NULL) {
        get_paths(from->left, targets);
    } 
    if (from->right != NULL) {
        get_paths(from->right, targets);
    } 
    if (from->bot != NULL) {
        get_paths(from->bot, targets);
    } 
    if (from->top != NULL) {
        get_paths(from->top, targets);
    } 
}

int count_paths(NodeList *start_nodes, PathMatrix *map) {
    int count = 0;
    for (int i = 0; i < start_nodes->length; i++) {
        NodeList *end_nodes = init_node_list(5);
        get_paths(start_nodes->nodes[i], end_nodes);
        count += end_nodes->length;
    }
    return count;
}

int solve_day10(const char *input) {
    FILE *file = fopen(input, "r");
    
    PathMatrix *mat = read_map(file);

    fclose(file);

    NodeList **nodes = get_nodes(mat);
    NodeList *start_nodes = nodes[0];

    int count = count_paths(start_nodes, mat);
    printf("Count: %d\n", count);

    return 0;
}
