#ifndef SRC_DATA_STRUCTURES_NODE_H_
#define SRC_DATA_STRUCTURES_NODE_H_

typedef struct node {
    void *value;
    struct node *next;
} t_node;

t_node *node_create(void *value);
void node_destroy(t_node *node);

#endif  // SRC_DATA_STRUCTURES_NODE_H_
