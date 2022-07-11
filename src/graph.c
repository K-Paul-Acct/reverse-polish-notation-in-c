#include "config.h"

void fill_plane(int plane[HEIGHT][WIDTH], t_queue *rpn);

int main() {
    int plane[HEIGHT][WIDTH] = {0};
    t_list *tokens = tokenize_input();
    if (tokens != NULL) {
        t_queue *rpn = shunting_yard_algorithm(tokens);
        if (rpn != NULL) {
            fill_plane(plane, rpn);
            print_plane(plane);
        } else {
            print_error();
        }
    } else {
        print_error();
    }
    return 0;
}

void fill_plane(int plane[HEIGHT][WIDTH], t_queue *rpn) {
    for (int i = 0; i < WIDTH; ++i) {
        double x = map_range(0, WIDTH - 1, X_LOW, X_HIGH, i);
        double y = compute_rpn(rpn, x);
        int y_mapped = round(map_range(Y_LOW, Y_HIGH, 0, HEIGHT - 1, y));
        if (y_mapped >= 0 && y_mapped <= HEIGHT - 1) {
            plane[y_mapped][i] = 1;
        }
    }
}
