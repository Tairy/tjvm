//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_OPERAND_STACK_H
#define TJVMSRC_OPERAND_STACK_H

#include "stdlib.h"

struct operand_stack {

};

struct operand_stack *new_operand_stack(u_int32_t max_stack);


void push_int(u_int32_t val);

u_int32_t pop_int();

void push_float(float val);

float pop_float();

void push_double(double val);

double pop_double();

void push_long(long val);

long pop_long();

void push_ref(void *ref);

void *pop_ref();

#endif //TJVMSRC_OPERAND_STACK_H
