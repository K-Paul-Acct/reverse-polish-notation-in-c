#ifndef SRC_DATA_IO_DATA_IO_H_
#define SRC_DATA_IO_DATA_IO_H_

#include "../data_structures/list.h"
#include "../data_structures/queue.h"
#include "../token/token.h"
#include "../config.h"

t_list *tokenize_input();
t_token *scan_number(char *c);
t_token *scan_function(char *c);
void print_plane(int plane[HEIGHT][WIDTH]);
void print_token(t_token *token);
void print_tokens(t_list *tokens);
void print_tokens_queue(t_queue *tokens);
void print_parsing_error();
void print_rpn_converting_error();
void print_computation_error();

#endif  // SRC_DATA_IO_DATA_IO_H_
