//
// Created by tairy on 2020/11/24.
//

#ifndef TJVMSRC_CLASS_REF_H
#define TJVMSRC_CLASS_REF_H

#include "class_file/constant_pool.h"
#include "runtime_constant_pool.h"

struct class_ref {
    char *classname;
    struct i_klass *clazz;
    struct runtime_constant_pool *rcp;
};

struct class_ref *new_class_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp);

void resolve_class_ref(struct class_ref *class_ref, struct i_klass *call_clazz);

#endif //TJVMSRC_CLASS_REF_H
