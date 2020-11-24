//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_LOCAL_VARS_H
#define TJVMSRC_LOCAL_VARS_H

#include "stdlib.h"
#include "slot.h"

struct local_vars {
    u_int32_t size;
    union slot **vars;
};

struct local_vars *new_local_vars(u_int32_t max_locals);

void *get_this(struct local_vars *vars);

#endif //TJVMSRC_LOCAL_VARS_H
