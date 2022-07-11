#ifndef SRC_RPN_RPN_H_
#define SRC_RPN_RPN_H_

#include "../config.h"

t_queue *shunting_yard_algorithm(t_list *tokens);
double compute_rpn(t_queue *rpn, double x);

#endif  // SRC_RPN_RPN_H_
