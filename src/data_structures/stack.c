#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

t_stack *stack_create() {
    t_stack *stack = (t_stack *)malloc(sizeof(t_stack));
    stack->top = NULL;
    return stack;
}

void stack_destroy(t_stack *self) {
    while (!stack_is_empty(self)) {
        free(stack_pop(self));
    }
    free(self);
}

void *stack_pop(t_stack *self) {
    void *value = NULL;
    if (!stack_is_empty(self)) {
        value = self->top->value;
        t_node *temp = self->top;
        self->top = self->top->next;
        node_destroy(temp);
    }
    return value;
}

void stack_push(t_stack *self, void *value) {
    t_node *node = node_create(value);
    node->next = self->top;
    self->top = node;
}

void *stack_pick(t_stack *self) {
    void *value = NULL;
    if (!stack_is_empty(self)) {
        value = self->top->value;
    }
    return value;
}

int stack_is_empty(t_stack *self) {
    return self->top == NULL;
}
