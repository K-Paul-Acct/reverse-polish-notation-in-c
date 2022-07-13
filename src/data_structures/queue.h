#ifndef SRC_DATA_STRUCTURES_QUEUE_H_
#define SRC_DATA_STRUCTURES_QUEUE_H_

#include "node.h"

typedef struct queue {
    t_node *head;
    t_node *tail;
} t_queue;

t_queue *queue_create();
t_queue *queue_create_copy(t_queue *sample);
void queue_destroy(t_queue *self);

void queue_enqueue(t_queue *self, void *value);
void *queue_dequeue(t_queue *self);
void *queue_pick(t_queue *self);
int queue_is_empty(t_queue *self);

#endif  // SRC_DATA_STRUCTURES_QUEUE_H_
