//
// Created by tairy on 2020/11/21.
//

#ifndef TJVMTEST_STACK_H
#define TJVMTEST_STACK_H

#include "stdlib.h"
#include "list.h"

typedef struct list stack;

#define STACK_INIT list_init
#define STACK_DESTROY list_destroy
#define STACK_PEEK(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)
#define STACK_SIZE LIST_SIZE

u_int8_t stack_push(stack *stack, const void *data);

u_int8_t stack_pop(stack *stack, void **data);

#endif //TJVMTEST_STACK_H
