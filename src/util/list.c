//
// Created by tairy on 2020/11/21.
//

#include "string.h"
#include "list.h"
#include "util.h"

/**
 * 初始化链表
 * @param list
 * @param destroy
 */
void list_init(struct list *list, void (*destroy)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

/**
 * 销毁链表
 * @param list
 */
void list_destroy(struct list *list) {
    void *data;
    while (LIST_SIZE(list) > 0) {
        if (list_rm_next(list, NULL, (void **) &data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(struct list));
}

/**
 * 在指定节点后面插入
 * 不指定则从头部插入
 * @param list 要操作的链表
 * @param element 指定的元素
 * @param data 要插入的数据
 * @return
 */
u_int8_t list_ins_next(struct list *list, struct list_element *element, const void *data) {
    struct list_element *new_element = NEW(struct list_element);

    if (new_element == NULL) {
        return -1;
    }

    new_element->data = (void *) data;

    // 如果元素为 NULL 就头插
    if (element == NULL) {
        if (LIST_SIZE(list) == 0) {
            new_element->next = list->head;
        }

        new_element->next = list->head;
        list->head = new_element;
    } else {
        if (element->next == NULL) {
            list->tail = new_element;
        }

        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;

    return 0;
}

/**
 * 删除指定节点后面的节点
 * 不指定则从头部移除
 * @param list 链表
 * @param element 指定的的节点
 * @param data 用于保存删除节点的数据
 * @return 成功返回 0, 失败返回 -1
 */
u_int8_t list_rm_next(struct list *list, struct list_element *element, void **data) {
    struct list_element *old_element;

    if (LIST_SIZE(list) == 0) {
        return -1;
    }

    if (element == NULL) {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (LIST_SIZE(list) == 1) {
            list->tail = NULL;
        }
    } else {
        if (element->next == NULL) {
            return -1;
        }
        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if (element->next == NULL) {
            list->tail = element;
        }
    }

    free(old_element);
    list->size--;

    return 0;
}