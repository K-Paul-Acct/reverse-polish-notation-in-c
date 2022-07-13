#include <stdio.h>
#include "../data_structures/list.h"
#include "../data_structures/queue.h"
#include "../token/token.h"
#include "../rpn/rpn.h"
#include "../data_io/data_io.h"

void compute_rpn_test();

int main() {
    compute_rpn_test();
    return 0;
}

void compute_rpn_test() {
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
    if (rpn_is_valid(rpn)) {
        double x;
        printf("Enter x: ");
        scanf("%lf", &x);
        double y = compute_rpn(rpn, x);
        printf("y = %lf\n", y);
        printf("Reversed Polish Notation saved:\n");
        print_tokens_queue(rpn);
    } else {
        printf("RPN is not valid.\n");
    }
    queue_destroy(rpn);
}
