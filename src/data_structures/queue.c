#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

t_queue *queue_create() {
    t_queue *queue = (t_queue *)malloc(sizeof(t_queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void queue_destroy(t_queue *self) {
    while (!queue_is_empty(self)) {
        free(queue_dequeue(self));
    }
    free(self);
}

void queue_enqueue(t_queue *self, void *value) {
    t_node *node = node_create(value);
    if (self->head == NULL) {
        self->head = node;
    } else {
        self->tail->next = node;
    }
    self->tail = node;
}

void *queue_dequeue(t_queue *self) {
    void *value = NULL;
    if (!queue_is_empty(self)) {
        value = self->head->value;
        t_node *temp = self->head;
        self->head = self->head->next;
        node_destroy(temp);
    }
    return value;
}

void *queue_pick(t_queue *self) {
    return self->head->value;
}

int queue_is_empty(t_queue *self) {
    return self->head == NULL;
}
