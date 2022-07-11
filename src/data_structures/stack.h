#ifndef SRC_DATA_STRUCTURES_STACK_H_
#define SRC_DATA_STRUCTURES_STACK_H_

#include "node.h"

typedef struct stack {
    int count;
    t_node *top;
} t_stack;

t_stack *stack_create();
void stack_destroy(t_stack *stack);

void *stack_pop(t_stack *stack);
void stack_push(t_stack *stack, void *value);
void *stack_pick(t_stack *stack);
int stack_is_empty(t_stack *stack);

#endif  // SRC_DATA_STRUCTURES_STACK_H_
