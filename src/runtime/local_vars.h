//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_LOCAL_VARS_H
#define TJVMSRC_LOCAL_VARS_H

#include "stdlib.h"
#include "slot.h"

struct local_vars {
    int32_t size;
    union slot **vars;
};

struct local_vars *new_local_vars(u_int32_t max_locals);

void *get_this(struct local_vars *vars);

void set_ref(struct local_vars *vars, u_int32_t index, void *ref);

void *get_ref(struct local_vars *vars, u_int32_t index);

void set_var(struct local_vars *vars, u_int32_t index, union slot *var);

union slot *get_var(struct local_vars *vars, u_int32_t index);

void set_int(struct local_vars *vars, u_int32_t index, int32_t val);

int32_t get_int(struct local_vars *vars, u_int32_t index);

void set_long(struct local_vars *vars, u_int32_t index, int64_t val);

int64_t get_long(struct local_vars *vars, u_int32_t index);

void set_float(struct local_vars *vars, u_int32_t index, float val);

float get_float(struct local_vars *vars, u_int32_t index);

void set_double(struct local_vars *vars, u_int32_t index, double val);

double get_double(struct local_vars *vars, u_int32_t index);

#endif //TJVMSRC_LOCAL_VARS_H
