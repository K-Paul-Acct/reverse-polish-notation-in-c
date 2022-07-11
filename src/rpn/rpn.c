#include "rpn.h"

t_queue *shunting_yard_algorithm(t_list *tokens) {
    t_queue *output_queue = queue_create();
    t_stack *operators_stack = stack_create();
    t_token *current_token;
    while (!queue_is_empty(tokens)) {
        current_token = (t_token *)queue_dequeue(tokens);
        t_operator *o_1 = current_token->operator;
        if (current_token->operand != NULL) {
            queue_enqueue(output_queue, current_token);
        } else if (o_1->type == FUNCTION) {
            stack_push(operators_stack, current_token);
        } else if (o_1->type == OPERATOR) {
            t_operator *o_2 = ((t_token *)stack_pick(operators_stack))->operator;
            while (!stack_is_empty(operators_stack) &&
                   o_2->type != L_PARENTHESIS &&
                   operator_compare_precedence(o_2, o_1) >= 0 &&
                   operator_get_associativity(o_1) == LEFT_TO_RIGHT) {
                queue_enqueue(output_queue, stack_pop(operators_stack));
                o_2 = ((t_token *)stack_pick(operators_stack))->operator;
            }
            stack_push(operators_stack, current_token);
        } else if (o_1->type == L_PARENTHESIS) {
            stack_push(operators_stack, current_token);
        } else if (current_token->operator->type == R_PARENTHESIS) {
            while (!stack_is_empty(operators_stack) &&
                   ((t_token *)stack_pick(operators_stack))->operator->type != L_PARENTHESIS) {
                queue_enqueue(output_queue, stack_pop(operators_stack));
            }
            if (stack_is_empty(operators_stack) ||
                ((t_token *)stack_pick(operators_stack))->operator->type != L_PARENTHESIS) {
                return NULL;
            }
            stack_pop(operators_stack);
            if (((t_token *)stack_pick(operators_stack))->operator->type == FUNCTION) {
                queue_enqueue(output_queue, stack_pop(operators_stack));
            }
        }
    }
    while (!stack_is_empty(operators_stack)) {
        if (((t_token *)stack_pick(operators_stack))->operator->type == L_PARENTHESIS ||
            ((t_token *)stack_pick(operators_stack))->operator->type == R_PARENTHESIS) {
            return NULL;
        }
        queue_enqueue(output_queue, stack_pop(operators_stack));
    }
    stack_destroy(operators_stack);
    queue_destroy(tokens);
    return output_queue;
}

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
