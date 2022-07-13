#ifndef SRC_RPN_RPN_H_
#define SRC_RPN_RPN_H_

#include "../data_structures/queue.h"
#include "../data_structures/list.h"

t_queue *shunting_yard_algorithm(t_list *tokens);
int rpn_is_valid(t_queue *rpn);
double compute_rpn(t_queue *rpn, double x);

#endif  // SRC_RPN_RPN_H_
