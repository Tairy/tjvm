//
// Created by tairy on 2020/11/24.
//

#ifndef TJVMSRC_FIELD_REF_H
#define TJVMSRC_FIELD_REF_H

#include "class_file/constant_pool.h"
#include "runtime_constant_pool.h"

struct field_ref {
    char *classname;
    struct i_klass *clazz;
    struct runtime_constant_pool *rcp;
    char *name;
    char *descriptor;
};

struct field_ref *new_field_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp);

#endif //TJVMSRC_FIELD_REF_H
