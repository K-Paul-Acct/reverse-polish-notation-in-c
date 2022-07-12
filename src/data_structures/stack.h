#ifndef SRC_DATA_STRUCTURES_STACK_H_
#define SRC_DATA_STRUCTURES_STACK_H_

#include "node.h"

typedef struct stack {
    t_node *top;
} t_stack;

t_stack *stack_create();
void stack_destroy(t_stack *self);

void *stack_pop(t_stack *self);
void stack_push(t_stack *self, void *value);
void *stack_pick(t_stack *self);
int stack_is_empty(t_stack *self);

#endif  // SRC_DATA_STRUCTURES_STACK_H_
