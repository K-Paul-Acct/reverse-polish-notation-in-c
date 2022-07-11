#ifndef SRC_DATA_STRUCTURES_QUEUE_H_
#define SRC_DATA_STRUCTURES_QUEUE_H_

#include "node.h"

typedef struct queue {
    int count;
    t_node *head;
    t_node *tail;
} t_queue;

t_queue *queue_create();
void queue_destroy(t_queue *queue);

void queue_enqueue(t_queue *queue, void *value);
void *queue_dequeue(t_queue *queue);
void *queue_get_at_index(t_queue *queue, int index);
int queue_is_empty(t_queue *queue);

#endif  // SRC_DATA_STRUCTURES_QUEUE_H_
