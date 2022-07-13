#include <stdio.h>
#include "../data_structures/list.h"
#include "../data_structures/queue.h"
#include "../token/token.h"
#include "../rpn/rpn.h"
#include "../data_io/data_io.h"

void rpn_is_valid_test();

int main() {
    rpn_is_valid_test();
    return 0;
}

void rpn_is_valid_test() {
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
    int res = rpn_is_valid(rpn);
    printf("RPN is valid: %d\n", res);
    queue_destroy(rpn);
}
