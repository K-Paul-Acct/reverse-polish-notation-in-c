#include <stdlib.h>
#include "queue.h"

t_queue *queue_create() {
    t_queue *queue = (t_queue *)malloc(sizeof(t_queue));
    queue->count = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void queue_destroy(t_queue *queue) {
    if (queue != NULL) {
        while (!queue_is_empty(queue)) {
            queue_dequeue(queue);
        }
        free(queue);
    }
}

void *queue_get_at_index(t_queue *queue, int index) {
    t_node *temp;
    void *res = NULL;
    if (queue != NULL) {
        temp = queue->head;
        int i = 0;
        for (; i < queue->count && i != index; ++i) {
            temp = temp->next;
        }
        if (i == index) {
            res = temp->value;
        }
    }
    return res;
}

void queue_enqueue(t_queue *queue, void *value) {
    if (queue != NULL) {
        t_node *node = node_create(value);
        if (queue->head == NULL) {
            queue->head = node;
        } else {
            queue->tail->next = node;
        }
        queue->tail = node;
        queue->count++;
    }
}

void *queue_dequeue(t_queue *queue) {
    void *value = NULL;
    if (queue != NULL && !queue_is_empty(queue)) {
        value = queue->head->value;
        t_node *temp = queue->head;
        queue->head = queue->head->next;
        node_destroy(temp);
        queue->count--;
    }
    return value;
}

int queue_is_empty(t_queue *queue) {
    return queue->count == 0;
}
