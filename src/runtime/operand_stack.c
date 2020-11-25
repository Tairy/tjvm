//
// Created by tairy on 2020/11/17.
//

#include "operand_stack.h"
#include "util/number.h"

struct operand_stack *new_operand_stack(u_int32_t max_stack) {
    if (max_stack > 0) {
        struct operand_stack *operand_stack = malloc(sizeof(struct operand_stack));

        operand_stack->size = 0;
        operand_stack->slots = malloc(sizeof(union slot *) * max_stack);

        for (int i = 0; i < max_stack; i++) {
            operand_stack->slots[i] = malloc(sizeof(union slot));
        }

        return operand_stack;
    }
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

void push_long(struct operand_stack *stack, int64_t val) {
    u_int32_t low = (u_int32_t) (val >> 32);
    stack->slots[stack->size++]->num = low;
    u_int32_t high = (u_int32_t) (val);
    stack->slots[stack->size++]->num = high;
}

int64_t pop_long(struct operand_stack *stack) {
    return (int64_t) stack->slots[--stack->size]->num | (int64_t) stack->slots[--stack->size]->num << 32;
}

void push_float(struct operand_stack *stack, float val) {
    stack->slots[stack->size++]->num = float_to_raw_int_bits(val);
}

float pop_float(struct operand_stack *stack) {
    return int_bits_to_float(stack->slots[--stack->size]->num);
}

void push_double(struct operand_stack *stack, double val) {
    int64_t int_val = double_to_raw_int_bits(val);
    push_long(stack, int_val);
}

double pop_double(struct operand_stack *stack) {
    int64_t int_val = pop_long(stack);
    return int_bits_to_double(int_val);
}

void *get_ref_from_top(struct operand_stack *stack, int32_t index) {
    return stack->slots[stack->size - index];
}