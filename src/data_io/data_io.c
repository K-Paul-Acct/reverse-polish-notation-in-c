#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../data_structures/stack.h"
#include "../data_structures/queue.h"
#include "data_io.h"

t_list *tokenize_input() {
    t_list *l = list_create();
    t_token *token, *last_token = NULL;
    int scan = 1, iterate = 1;
    char c;
    while (iterate) {
        token = NULL;
        if (scan) {
            c = getchar();
        }
        scan = 1;
        if (c == ' ') {
            continue;
        } else if (c == '\n') {
            iterate = 0;
            continue;
        } else if ('0' <= c && c <= '9') {
            token = scan_number(&c);
            scan = 0;
        } else if (c == 'x') {
            token = token_create_variable('x');
        } else if (c == '-' &&
                   (last_token == NULL || last_token->symbol == '(' ||
                   last_token->type == OPERATOR)) {
            token = token_create_function(NEGATE);
        } else if (is_operator(c)) {
            token = token_create_operator(c);
        } else if (c == '(' || c == ')') {
            token = token_create_parenthesis(c);
        } else {
            token = scan_function(&c);
            scan = 0;
        }
        if (token == NULL) {
            list_destroy(l);
            l = NULL;
            iterate = 0;
        } else {
            list_push_back(l, token);
            last_token = token;
        }
    }
    return l;
}

t_token *scan_function(char *c) {
    t_token *token = NULL;
    char func[8] = {0};
    int index = 1, iterate = 1;
    func[0] = *c;
    while (iterate) {
        *c = getchar();
        if (*c == '\n' || *c == '(' || index == 7) {
            iterate = 0;
        } else {
            func[index++] = *c;
        }
    }
    if (*c == '(') {
        char func_letter = '\0';
        if (!strcmp("sin", func)) {
            func_letter = SIN;
        } else if (!strcmp("cos", func)) {
            func_letter = COS;
        } else if (!strcmp("tan", func)) {
            func_letter = TAN;
        } else if (!strcmp("cot", func)) {
            func_letter = COT;
        } else if (!strcmp("arcsin", func)) {
            func_letter = ARCSIN;
        } else if (!strcmp("arccos", func)) {
            func_letter = ARCCOS;
        } else if (!strcmp("arctan", func)) {
            func_letter = ARCTAN;
        } else if (!strcmp("arccot", func)) {
            func_letter = ARCCOT;
        } else if (!strcmp("exp", func)) {
            func_letter = EXP;
        } else if (!strcmp("ln", func)) {
            func_letter = LN;
        } else if (!strcmp("sqrt", func)) {
            func_letter = SQRT;
        } else if (!strcmp("fact", func)) {
            func_letter = FACT;
        }
        if (func_letter != '\0') {
            token = token_create_function(func_letter);
        }
    }
    return token;
}

t_token *scan_number(char *c) {
    t_token *token = NULL;
    int points_counter = 0, iterate = 1;
    double number = 0;
    t_stack *before_point_s = stack_create();
    t_queue *after_point_q = queue_create();
    while (iterate) {
        if (*c == '\n') {
            iterate = 0;
            continue;
        } else if (*c == '.') {
            if (points_counter++ != 0) {
                iterate = 0;
            }
        } else if (*c >= '0' && *c <= '9') {
            int *d = (int *)malloc(sizeof(int));
            *d = *c - '0';
            if (points_counter) {
                queue_enqueue(after_point_q, d);
            } else {
                stack_push(before_point_s, d);
            }
        } else {
            iterate = 0;
            continue;
        }
        *c = getchar();
    }
    for (int i = 0; !stack_is_empty(before_point_s); ++i) {
        int *d = (int *)stack_pop(before_point_s);
        number += *d * pow(10, i);
        free(d);
    }
    for (int i = -1; !queue_is_empty(after_point_q); --i) {
        int *d = (int *)queue_dequeue(after_point_q);
        number += *d * pow(10, i);
        free(d);
    }
    token = token_create_number(number);
    stack_destroy(before_point_s);
    queue_destroy(after_point_q);
    return token;
}

void print_plane(int plane[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%c", plane[i][j] ? '*' : '.');
        }
        printf("\n");
    }
}

void print_parsing_error() {
    printf("An error occurred while parsing.\n");
}
