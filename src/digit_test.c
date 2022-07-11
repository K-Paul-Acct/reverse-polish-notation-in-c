#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_structures/stack.h"

double get_num(char *c);

int main() {
    char c = getchar();
    double number = get_num(&c);
    printf("%lf", number);
    return 0;
}

double get_num(char *c) {
    int points_counter = 0, exit = 0;
    double number = 0;
    t_stack *before_point_stack = stack_create();
    t_stack *after_point_stack = stack_create();
    while (!exit) {
        if (*c == '.') {
            points_counter++;
        } else if (*c >= '0' && *c <= '9') {
            if (points_counter == 1) {
                int *digit = (int *)malloc(sizeof(int));
                *digit = *c - '0';
                stack_push(after_point_stack, digit);
            } else if (points_counter == 0) {
                int *digit = (int *)malloc(sizeof(int));
                *digit = *c - '0';
                stack_push(before_point_stack, digit);
            } else {
                exit = 1;
            }
        } else {
            exit = 1;
        }
        if (!exit) {
            *c = getchar();
        }
    }
    if (points_counter < 2) {
        for (int i = 0; !stack_is_empty(before_point_stack); ++i) {
            int *digit = (int *)stack_pop(before_point_stack);
            number += pow(10, i) * *digit;
            free(digit);
        }
        for (int i = -after_point_stack->count; !stack_is_empty(after_point_stack); ++i) {
            int *digit = (int *)stack_pop(after_point_stack);
            number += pow(10, i) * *digit;
            free(digit);
        }
    }
    stack_destroy(before_point_stack);
    stack_destroy(after_point_stack);
    return number;
}
