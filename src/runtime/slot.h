//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_SLOT_H
#define TJVMSRC_SLOT_H

#include "stdlib.h"

union slot {
    u_int32_t num;
    void *ref;
};

void set_ref(union slot **vars, u_int32_t index, void *ref);

void *get_ref(union slot **vars, u_int32_t index);

void set_var(union slot **vars, u_int32_t index, union slot *var);

union slot *get_var(union slot **vars, u_int32_t index);

void set_int(union slot **vars, u_int32_t index, int32_t val);

int32_t get_int(union slot **vars, u_int32_t index);

void set_long(union slot **vars, u_int32_t index, int64_t val);

int64_t get_long(union slot **vars, u_int32_t index);

void set_float(union slot **vars, u_int32_t index, float val);

float get_float(union slot **vars, u_int32_t index);

void set_double(union slot **vars, u_int32_t index, double val);

double get_double(union slot **vars, u_int32_t index);

#endif //TJVMSRC_SLOT_H
