#ifndef SRC_DATA_STRUCTURES_NODE_H_
#define SRC_DATA_STRUCTURES_NODE_H_

#include "../config.h"

typedef struct node {
    void *value;
    struct node *next;
} t_node;

t_node *node_create(void *value);
void node_destroy(t_node *self);

#endif  // SRC_DATA_STRUCTURES_NODE_H_
