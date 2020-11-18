//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_OOP_H
#define TJVMSRC_OOP_H

#include "stdlib.h"
#include "class.h"

struct oop {
};

struct instance_oop {

};

struct array_oop {
    u_int32_t length;
};

union slot get_instant_vars(struct instance_oop *object);

struct instance_oop *resolve_string_reference(struct i_klass *clazz, char *str);

#endif //TJVMSRC_OOP_H
