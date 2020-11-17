//
// Created by tairy on 2020/11/17.
//

#include "operand_stack.h"

struct operand_stack *new_operand_stack(u_int32_t max_stack) {
    return NULL;
}

void push_ref(struct operand_stack *stack, void *ref) {
    stack->slots[stack->size++]->ref = ref;
}

void *pop_ref(struct operand_stack *stack) {
    return stack->slots[--stack->size]->ref;
}

void *top_ref(struct operand_stack *stack) {
    return stack->slots[stack->size - 1]->ref;
}

void push_var(struct operand_stack *stack, union slot *var) {
    stack->slots[stack->size++] = var;
}

union slot *pop_var(struct operand_stack *stack) {
    return stack->slots[--stack->size];
}

void push_boolean(struct operand_stack *stack, int8_t value) {
    stack->slots[stack->size++]->num = value;
}

int8_t pop_boolean(struct operand_stack *stack) {
    return (int8_t) (stack->slots[--stack->size]->num);
}

void push_int(struct operand_stack *stack, int32_t val) {
    stack->slots[stack->size++]->num = val;
}

int32_t pop_int(struct operand_stack *stack) {
    return stack->slots[--stack->size]->num;
}

void push_long(struct operand_stack *stack, int64_t val);

int64_t pop_long(struct operand_stack *stack);

void push_float(struct operand_stack *stack, float val);

float pop_float(struct operand_stack *stack);

void push_double(struct operand_stack *stack, double val);

double pop_double(struct operand_stack *stack);

void *get_ref_from_top(struct operand_stack *stack, int32_t index);