//
// Created by tairy on 2020/11/21.
//

#ifndef TJVMTEST_LIST_H
#define TJVMTEST_LIST_H

#include "stdlib.h"

#define LIST_SIZE(list) ((list)->size)
#define LIST_HEAD(list) ((list)->head)
#define LIST_TAIL(list) ((list)->tail)
#define LIST_IS_HEAD(list, element) ((element) == (list)->head ? 1 : 0)
#define LIST_IS_TAIL(list, element) ((element) == (list)->tail ? 1 : 0)
#define LIST_DATA(element) ((element)->data)
#define LIST_NEXT(element) ((element)->next)

struct list_element {
    void *data;
    struct list_element *next;
};

struct list {
    u_int32_t size;

    u_int8_t (*match)(const void *key1, const void *key2);

    void (*destroy)(void *data);

    struct list_element *head;

    struct list_element *tail;
};

/**
 * public interface
 */

void list_init(struct list *list, void (*destroy)(void *data));

void list_destroy(struct list *list);

u_int8_t list_ins_next(struct list *list, struct list_element *element, const void *data);

u_int8_t list_rm_next(struct list *list, struct list_element *element, void **data);


#endif //TJVMTEST_LIST_H
