//
// Created by tairy on 2020/11/21.
//

#include "stack.h"

u_int8_t stack_push(stack *stack, const void *data) {
    return list_ins_next(stack, NULL, data);
}

u_int8_t stack_pop(stack *stack, void **data) {
    return list_rm_next(stack, NULL, data);
}
