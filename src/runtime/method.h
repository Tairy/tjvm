//
// Created by tairy on 2020/11/24.
//

#ifndef TJVMSRC_METHOD_H
#define TJVMSRC_METHOD_H

#include "class.h"
#include "stdlib.h"

struct method {
    struct i_klass *clazz;
    u_int16_t access_flags;
    char *name;
    char *descriptor;

    u_int32_t max_locals;
    u_int32_t max_stack;
    u_int32_t arg_count;
    u_int32_t code_len;
    char *code;
};

struct methods {
    u_int32_t size;
    struct method **methods;
};

struct methods *new_methods(struct i_klass *clazz, struct member_infos *origin_methods);

#endif //TJVMSRC_METHOD_H
