#include <stdio.h>
#include "logic.h"
#include "../data_io/data_io.h"

void tokenize_input_test();
void print_token(t_token *token);
void shunting_yard_algorithm_test();
void fill_plane_test();
t_queue *get_test_data();

int main() {
    //tokenize_input_test();
    shunting_yard_algorithm_test();
    //fill_plane_test();
    printf("\nDone\n");
    return 0;
}

t_queue *get_test_data() {
    t_operator *or_1 = operator_create(FUNCTION, 's');
    t_operator *or_2 = operator_create(L_PARENTHESIS, '(');
    t_operator *or_3 = operator_create(FUNCTION, 'c');
    t_operator *or_4 = operator_create(L_PARENTHESIS, '(');
    t_operand *od_1 = operand_create(NUMBER, 2);
    t_operator *or_5 = operator_create(OPERATOR, '*');
    t_operand *od_2 = operand_create(VARIABLE, 'x');
    t_operator *or_6 = operator_create(R_PARENTHESIS, ')');
    t_operator *or_7 = operator_create(R_PARENTHESIS, ')');

    t_token *t_1 = token_create(or_1, NULL);
    t_token *t_2 = token_create(or_2, NULL);
    t_token *t_3 = token_create(or_3, NULL);
    t_token *t_4 = token_create(or_4, NULL);
    t_token *t_5 = token_create(NULL, od_1);
    t_token *t_6 = token_create(or_5, NULL);
    t_token *t_7 = token_create(NULL, od_2);
    t_token *t_8 = token_create(or_6, NULL);
    t_token *t_9 = token_create(or_7, NULL);

    t_queue *tokens = queue_create();

    queue_enqueue(tokens, t_1);
    queue_enqueue(tokens, t_2);
    queue_enqueue(tokens, t_3);
    queue_enqueue(tokens, t_4);
    queue_enqueue(tokens, t_5);
    queue_enqueue(tokens, t_6);
    queue_enqueue(tokens, t_7);
    queue_enqueue(tokens, t_8);
    queue_enqueue(tokens, t_9);

    return tokens;
}

void tokenize_input_test() {
    t_queue *tokens = tokenize_input();
    printf("%p\n", tokens);
    if (tokens != NULL) {
        while (!queue_is_empty(tokens)) {
            t_token *token = (t_token *)queue_dequeue(tokens);
            print_token(token);
            token_destroy(token);
        }
        printf("\n");
        queue_destroy(tokens);
    }
}

void print_token(t_token *token) {
    if (token != NULL) {
        if (token->operand != NULL) {
            if (token->operand->type == VARIABLE) {
                printf("%c  ", token->operand->letter);
            } else {
                printf("%.2lf  ", token->operand->value);
            }
        } else if (token->operator != NULL) {
            printf("%c  ", token->operator->symbol);
        }
    }
}

void shunting_yard_algorithm_test() {
    t_queue *tokens = tokenize_input();
    t_queue *output = shunting_yard_algorithm(tokens);

    if (output != NULL) {
        while (!queue_is_empty(output)) {
            t_token *token = (t_token *)queue_dequeue(output);
            print_token(token);
            token_destroy(token);
        }
        queue_destroy(output);
    }        
}

void fill_plane_test() {
    int plane[HEIGHT][WIDTH] = {0};
    t_queue *tokens = get_test_data();
    t_queue *rpn = shunting_yard_algorithm(tokens);
    if (rpn != NULL) {
        fill_plane(plane, rpn);
        print_plane(plane);
    }
}
