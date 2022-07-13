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
            while (!stack_is_empty(s) &&
                   (temp->type == OPERATOR || (temp->type == FUNCTION && temp->symbol == NEGATE)) &&
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

int rpn_is_valid(t_queue *rpn) {
    t_queue *q = queue_create_copy(rpn);
    int operands = 0;
    while (!queue_is_empty(q)) {
        t_token *t = (t_token *)queue_dequeue(q);
        if (t->type == NUMBER || t->type == VARIABLE) {
            operands++;
        } else if (t->type == OPERATOR) {
            operands--;
        }
    }
    queue_destroy(q);
    return operands == 1;
}

double compute_rpn(t_queue *rpn, double x) {
    t_queue *q = queue_create_copy(rpn);
    t_stack *s = stack_create();
    while (!queue_is_empty(q)) {
        t_token *t = (t_token *)queue_dequeue(q);
        if (t->type == NUMBER) {
            t_token *temp = token_create_number(t->value);
            stack_push(s, temp);
        } else if (t->type == VARIABLE) {
            t_token *temp = token_create_number(x);
            stack_push(s, temp);
        } else if (t->type == FUNCTION) {
            t_token *operand = (t_token *)stack_pop(s);
            t_token *res = operator_apply_unary(t, operand);
            stack_push(s, res);
            token_destroy(operand);
        } else if (t->type == OPERATOR) {
            t_token *operand_1 = (t_token *)stack_pop(s);
            t_token *operand_2 = (t_token *)stack_pop(s);
            t_token *res = operator_apply_binary(t, operand_2, operand_1);
            stack_push(s, res);
            token_destroy(operand_1);
            token_destroy(operand_2);
        }
    }
    t_token *res = (t_token *)stack_pop(s);
    double y = res->value;
    token_destroy(res);
    queue_destroy(q);
    stack_destroy(s);
    return y;
}
