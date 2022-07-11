#ifndef SRC_DATA_IO_DATA_IO_H_
#define SRC_DATA_IO_DATA_IO_H_

#include "../config.h"

t_list *tokenize_input();
void print_plane(int plane[HEIGHT][WIDTH]);
void print_parsing_error();

#endif  // SRC_DATA_IO_DATA_IO_H_
