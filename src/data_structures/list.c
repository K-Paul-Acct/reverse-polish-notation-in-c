#include "list.h"

t_list *list_create() {
    t_list *list = (t_list *)malloc(sizeof(t_list));
    list->count = 0;
    list->front = NULL;
    list->back = NULL;
    return list;
}

void list_destroy(t_list *self) {
    while(!list_is_empty(self)) {
        free(list_pop_front(self));
    }
}

//void *list_front(t_list *self);
//void *list_back(t_list *self);
//void list_push_front(t_list *self, void *value);

void list_push_back(t_list *self, void *value) {
    t_node *node = node_create(value);
    if (self->front == NULL) {
        self->front = node;
    } else {
        self->back->next = node;
    }
    self->back = node;
    self->count++;
}

//void list_insert(t_list *self);

void *list_pop_front(t_list *self) {
    void *value = NULL;
    if (!list_is_empty(self)) {
        value = self->front->value;
        t_node *temp = self->front;
        self->front = self->front->next;
        node_destroy(temp);
        self->count--;
    }
    return value;
}

///void *list_pop_back(t_list *self);

void *list_get_at_index(t_list *self, int index) {
    void *value = NULL;
    int i = 1;
    t_node *temp = self->front;
    for (; i != index + 1 && i < list_size(self); ++i) {
        temp = temp->next;
    }
    if (temp != NULL) {
        value = temp->value;
    }
    return value;
}

int list_is_empty(t_list *self) {
    return self->count == 0;
}

int list_size(t_list *self) {
    return self->count;
}
