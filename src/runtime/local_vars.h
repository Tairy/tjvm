//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_LOCAL_VARS_H
#define TJVMSRC_LOCAL_VARS_H

#include "stdlib.h"

struct local_vars {

    u_int32_t size;
};

struct local_vars *new_local_vars(u_int32_t max_locals);

void set_int(u_int32_t index, u_int32_t val);

u_int32_t get_int(u_int32_t index);

void set_float(u_int32_t index, float val);

float get_float(u_int32_t index);

void set_double(u_int32_t index, double val);

double get_double(u_int32_t index);

void set_long(u_int32_t index, long val);

long get_long(u_int32_t index);


#endif //TJVMSRC_LOCAL_VARS_H
