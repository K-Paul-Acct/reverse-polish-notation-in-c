#include "rpn.h"

t_queue *shunting_yard_algorithm(t_list *tokens) {
    t_queue *q = queue_create();
    t_stack *s = stack_create();
    while (!list_is_empty(tokens)) {
        t_token *t = (t_token *)list_pop_front(tokens);
        if (t->type == NUMBER || t->type == VARIABLE) {
            queue_enqueue(q, t);
        } else if (t->type == FUNCTION) {
            stack_push(s, t);
        } else if (t->type == OPERATOR) {
            while (!stack_is_empty(s) &&
                   ((t_token *)stack_pick(s))->type == OPERATOR &&
                   operator_get_associativity(t) == LEFT &&
                   operator_compare_precedence(t, (t_token *)stack_pick(s)) <= 0) {
                queue_enqueue(q, stack_pop(s));
            }
        } else if (t->symbol == '(') {
            stack_push(s, t);
        } else if (t->symbol == ')') {
            while (((t_token *)stack_pick(s))->symbol != '(') {
                if (stack_is_empty(s)) {
                    // Error handling.
                }
                queue_enqueue(q, stack_pop(s));
            }
            stack_pop(s);
            if (((t_token *)stack_pick(s))->type == FUNCTION) {
                queue_enqueue(q, stack_pop(s));
            }
        }
    }
    while (!stack_is_empty(s)) {
        if (((t_token *)stack_pick(s))->symbol == ')') {
            // Error handling.
        }
        queue_enqueue(q, stack_pop(s));
    }
    stack_destroy(s);
    return q;
}
/*
double compute_rpn(t_queue *rpn, double x) {
    double y = 0;
    if (rpn != NULL) {
        t_stack *stack = stack_create();
        for (int i = 0; i < rpn->count; ++i) {
            t_token *token = (t_token *)queue_get_at_index(rpn, i);
            if (token->operand != NULL) {
                if (token->operand->type == VARIABLE) {
                    t_operand *variable = operand_create(NUMBER, x);
                    stack_push(stack, variable);
                } else {
                    stack_push(stack, token->operand);
                }
            } else if (token->operator->type == FUNCTION) {
                t_operand *o = (t_operand *)stack_pop(stack);
                stack_push(stack, operator_apply_unary(token->operator, o));
            } else if (token->operator->type == OPERATOR) {
                t_operand *o_1 = (t_operand *)stack_pop(stack);
                t_operand *o_2 = (t_operand *)stack_pop(stack);
                stack_push(stack, operator_apply_binary(token->operator, o_2, o_1));
            }
        }
        y = ((t_operand *)stack_pop(stack))->value;
    }
    return y;
}
*/