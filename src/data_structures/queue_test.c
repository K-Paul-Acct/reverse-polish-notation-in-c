#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"
#include "../types/token.h"
#include "../types/operator.h"

int main() {
    t_operator *o_1 = operator_create(OPERATOR, '+');
    t_operator *o_2 = operator_create(OPERATOR, '/');
    t_operator *o_3 = operator_create(OPERATOR, '-');
    t_operator *o_4 = operator_create(OPERATOR, '*');

    t_queue *queue = queue_create();
    t_stack *stack = stack_create();

    queue_enqueue(queue, o_1);
    queue_enqueue(queue, o_2);
    queue_enqueue(queue, o_3);
    queue_enqueue(queue, o_4);

    for (int i = 0; i < queue->count; ++i) {
        printf("Index %d, value %c\n", i, ((t_operator *)queue_get_at_index(queue, i))->symbol);
    }

    stack_push(stack, o_1);
    stack_push(stack, o_2);
    stack_push(stack, o_3);
    stack_push(stack, o_4);

    // t_operator *de_1 = (t_operator *)queue_dequeue(queue);
    // t_operator *de_2 = (t_operator *)queue_dequeue(queue);
    // t_operator *de_3 = (t_operator *)queue_dequeue(queue);
    // t_operator *de_4 = (t_operator *)queue_dequeue(queue);

    t_operator *pop_1 = (t_operator *)stack_pop(stack);
    t_operator *pop_2 = (t_operator *)stack_pop(stack);
    t_operator *pop_3 = (t_operator *)stack_pop(stack);
    t_operator *pop_4 = (t_operator *)stack_pop(stack);

    printf("Enqueue order: %c -> %c -> %c -> %c\n", o_1->symbol, o_2->symbol, o_3->symbol, o_4->symbol);
    //printf("Dequeue order: %c -> %c -> %c -> %c\n", de_1->symbol, de_2->symbol, de_3->symbol, de_4->symbol);
    printf("\n");
    printf("Push order: %c -> %c -> %c -> %c\n", o_1->symbol, o_2->symbol, o_3->symbol, o_4->symbol);
    printf("Pop order: %c -> %c -> %c -> %c\n", pop_1->symbol, pop_2->symbol, pop_3->symbol, pop_4->symbol);

    queue_destroy(queue);
    stack_destroy(stack);
    operator_destroy(o_1);
    operator_destroy(o_2);
    operator_destroy(o_3);
    operator_destroy(o_4);

    return 0;
}
