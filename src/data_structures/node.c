#include <stdlib.h>
#include "node.h"

t_node *node_create(void *value) {
    t_node *node = (t_node *)malloc(sizeof(t_node));
    node->value = value;
    node->next = NULL;
    return node;
}

void node_destroy(t_node *node) {
    if (node != NULL) {
        free(node);
    }
}
