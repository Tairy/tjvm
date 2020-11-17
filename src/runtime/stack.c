//
// Created by tairy on 2020/11/17.
//

#include "stack.h"

struct stack *create_stack(u_int32_t max_size) {
    struct stack *stack = malloc(sizeof(struct stack));
    stack->max_size = max_size;
    return stack;
}
