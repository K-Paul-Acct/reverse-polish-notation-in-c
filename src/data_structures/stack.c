#include <stdlib.h>
#include "stack.h"

t_stack *stack_create() {
    t_stack *stack = (t_stack *)malloc(sizeof(t_stack));
    stack->count = 0;
    stack->top = NULL;
    return stack;
}

void stack_destroy(t_stack *stack) {
    if (stack != NULL) {
        while (!stack_is_empty(stack)) {
            stack_pop(stack);
        }
        free(stack);
    }
}

void *stack_pop(t_stack *stack) {
    void *value = NULL;
    if (stack != NULL && !stack_is_empty(stack)) {
        value = stack->top->value;
        t_node *temp = stack->top;
        stack->top = stack->top->next;
        node_destroy(temp);
        stack->count--;
    }
    return value;
}

void stack_push(t_stack *stack, void *value) {
    if (stack != NULL) {
        t_node *node = node_create(value);
        node->next = stack->top;
        stack->top = node;
        stack->count++;
    }
}

void *stack_pick(t_stack *stack) {
    void *value = NULL;
    if (stack != NULL && stack->top != NULL) {
        value = stack->top->value;
    }
    return value;
}

int stack_is_empty(t_stack *stack) {
    return stack->count == 0;
}
