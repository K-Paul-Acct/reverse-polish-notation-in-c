#include <stdio.h>
#include "../token/token.h"
#include "../data_structures/stack.h"
#include "rpn.h"

t_queue *shunting_yard_algorithm(t_list *tokens) {
    t_queue *q = queue_create();
    t_stack *s = stack_create();
    int iterate = 1;
    while (iterate && !list_is_empty(tokens)) {
        t_token *t = (t_token *)list_pop_front(tokens);
        if (t->type == NUMBER || t->type == VARIABLE) {
            queue_enqueue(q, t);
        } else if (t->type == FUNCTION) {
            stack_push(s, t);
        } else if (t->type == OPERATOR) {
            t_token *temp = (t_token *)stack_pick(s);
            int associativity = operator_get_associativity(t);
            while (!stack_is_empty(s) && temp->type == OPERATOR &&
                   (operator_compare_precedence(temp, t) > 0 ||
                   (operator_compare_precedence(temp, t) == 0 && associativity == LEFT))) {
                queue_enqueue(q, stack_pop(s));
                temp = (t_token *)stack_pick(s);
            }
            stack_push(s, t);
        } else if (t->symbol == '(') {
            stack_push(s, t);
        } else if (t->symbol == ')') {
            t_token *temp = (t_token *)stack_pop(s);
            while (temp && temp->symbol != '(') {
                queue_enqueue(q, temp);
                temp = (t_token *)stack_pop(s);
            }
            // Mismanatched parentheses. Closing parenthesis without opening parenthesis.
            if (temp == NULL) {
                token_destroy(t);
                queue_destroy(q);
                iterate = 0;
                q = NULL;
                continue;
            } else {
                token_destroy(t);
                token_destroy(temp);
            }
            if (!stack_is_empty(s) && ((t_token *)stack_pick(s))->type == FUNCTION) {
                queue_enqueue(q, stack_pop(s));
            }
        }
    }
    while (iterate && !stack_is_empty(s)) {
        t_token *temp = (t_token *)stack_pop(s);
        // Mismanatched parentheses. Opening parenthesis without closing parenthesis.
        if (temp->type == PARENTHESIS) {
            token_destroy(temp);
            queue_destroy(q);
            iterate = 0;
            q = NULL;
            continue;
        }
        queue_enqueue(q, temp);
    }
    list_destroy(tokens);
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