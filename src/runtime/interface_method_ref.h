//
// Created by tairy on 2020/11/24.
//

#ifndef TJVMSRC_INTERFACE_METHOD_REF_H
#define TJVMSRC_INTERFACE_METHOD_REF_H

#include "class_file/constant_pool.h"
#include "runtime_constant_pool.h"


struct interface_method_ref {
    char *classname;
    struct i_klass *clazz;
    struct runtime_constant_pool *rcp;
    char *name;
    char *descriptor;
};

struct interface_method_ref *
new_interface_method_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp);


#endif //TJVMSRC_INTERFACE_METHOD_REF_H
