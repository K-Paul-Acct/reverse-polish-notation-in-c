#include <stdio.h>
#include "rpn/rpn.h"
#include "algorithms/algorithms.h"
#include "data_structures/list.h"
#include "data_structures/queue.h"
#include "data_io/data_io.h"
#include "config.h"

void fill_plane(int plane[HEIGHT][WIDTH], t_queue *rpn);

int main() {
    int plane[HEIGHT][WIDTH] = {0};
    t_list *tokens = tokenize_input();
    if (tokens) {
        t_queue *rpn = shunting_yard_algorithm(tokens);
        if (rpn) {
            printf("Reverse Polish Notation:\n");
            print_tokens_queue(rpn);
            if (rpn_is_valid(rpn)) {
                fill_plane(plane, rpn);
                print_plane(plane);
            } else {
                print_computation_error();
            }
            queue_destroy(rpn);
        } else {
            print_rpn_converting_error();
        }
    } else {
        print_parsing_error();
    }
    return 0;
}

void fill_plane(int plane[HEIGHT][WIDTH], t_queue *rpn) {
    double step = (X_HIGH - X_LOW) / (double)(WIDTH - 1) / 10.0;
    for (double x = X_LOW; x <= X_HIGH; x += step) {
        double y = compute_rpn(rpn, x);
        if (y >= Y_LOW && y <= Y_HIGH) {
            int x_mapped = round(map_range(X_LOW, X_HIGH, -0.4, WIDTH - 0.6, x));
            int y_mapped = round(map_range(Y_LOW, Y_HIGH, -0.4, HEIGHT - 0.6, y));
            plane[HEIGHT - y_mapped - 1][x_mapped] = 1;
        }
    }
}
