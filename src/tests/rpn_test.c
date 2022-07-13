#include <stdio.h>
#include "../data_structures/list.h"
#include "../data_structures/queue.h"
#include "../token/token.h"
#include "../rpn/rpn.h"
#include "../data_io/data_io.h"

void shunting_yard_algorithm_test();

int main() {
    shunting_yard_algorithm_test();
    return 0;
}

void shunting_yard_algorithm_test() {
    t_list *tokens = tokenize_input();
    if (tokens == NULL) {
        printf("Error: Could not tokenize input.\n");
        return;
    }
    t_queue *rpn = shunting_yard_algorithm(tokens);
    if (rpn == NULL) {
        printf("Error: Could not convert to RPN.\n");
        return;
    }
    while (!queue_is_empty(rpn)) {
        t_token *token = (t_token *)queue_dequeue(rpn);
        print_token(token);
        token_destroy(token);
    }
    printf("\n");
    queue_destroy(rpn);
}
