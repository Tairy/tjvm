//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_OPERAND_STACK_H
#define TJVMSRC_OPERAND_STACK_H

#include "stdlib.h"
#include "slot.h"

struct operand_stack {

    int32_t size;

    union slot **slots;
};

struct operand_stack *new_operand_stack(u_int32_t max_stack);

void push_ref(struct operand_stack *stack, void *ref);

void *pop_ref(struct operand_stack *stack);

void *top_ref(struct operand_stack *stack);

void push_var(struct operand_stack *stack, union slot *var);

union slot *pop_var(struct operand_stack *stack);

void push_boolean(struct operand_stack *stack, int8_t value);

int8_t pop_boolean(struct operand_stack *stack);

void push_int(struct operand_stack *stack, int32_t val);

int32_t pop_int(struct operand_stack *stack);

void push_long(struct operand_stack *stack, int64_t val);

int64_t pop_long(struct operand_stack *stack);

void push_float(struct operand_stack *stack, float val);

float pop_float(struct operand_stack *stack);

void push_double(struct operand_stack *stack, double val);

double pop_double(struct operand_stack *stack);

void *get_ref_from_top(struct operand_stack *stack, int32_t index);

#endif //TJVMSRC_OPERAND_STACK_H
