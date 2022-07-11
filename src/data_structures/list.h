#ifndef SRC_DATA_STRUCTURES_LIST_H_
#define SRC_DATA_STRUCTURES_LIST_H_

#include "../config.h"

typedef struct list {
    int count;
    t_node *front;
    t_node *back;
} t_list;

t_list *list_create();
void list_destroy(t_list *self);

//void *list_front(t_list *self);
//void *list_back(t_list *self);
//void list_push_front(t_list *self, void *value);

void list_push_back(t_list *self, void *value);

//void list_insert(t_list *self);

void *list_pop_front(t_list *self);

////void *list_pop_back(t_list *self);

void *list_get_at_index(t_list *self, int index);
int list_is_empty(t_list *self);
int list_size(t_list *self);

#endif  // SRC_DATA_STRUCTURES_LIST_H_
