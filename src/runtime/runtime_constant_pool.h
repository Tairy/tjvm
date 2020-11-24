//
// Created by tairy on 2020/11/17.
//
// 运行时常量池，类加载时解析

#ifndef TJVMSRC_RUNTIME_CONSTANT_POOL_H
#define TJVMSRC_RUNTIME_CONSTANT_POOL_H

#include "class_file/constant_pool.h"
#include "class_file/class_file.h"
#include "runtime/class.h"
#include "class.h"

struct class_ref {
    char *classname;
    struct i_klass *clazz;
    struct runtime_constant_pool *rcp;
};

struct field_ref {
    char *classname;
    struct i_klass *clazz;
    struct runtime_constant_pool *rcp;
    char *name;
    char *descriptor;
};

struct method_ref {
    char *classname;
    struct i_klass *clazz;
    struct runtime_constant_pool *rcp;
    char *name;
    char *descriptor;
};

struct interface_method_ref {
    char *classname;
    struct i_klass *clazz;
    struct runtime_constant_pool *rcp;
    char *name;
    char *descriptor;
};

struct runtime_constant_pool_info {
    u_int8_t type;
    void *data;
};

struct runtime_constant_pool {
    u_int32_t size;
    struct runtime_constant_pool_info **infos;
};

struct class_ref *new_class_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp,
                                struct class_loader *class_loader);

struct field_ref *new_field_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp,
                                struct class_loader *class_loader);

struct method_ref *
new_method_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp,
               struct class_loader *class_loader);

struct interface_method_ref *
new_interface_method_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp,
                         struct class_loader *class_loader);

struct runtime_constant_pool *build_runtime_constant_pool(struct class_loader *class_loader, struct cp *cp);

struct runtime_constant_pool_info *get_runtime_constant_pool_info(struct runtime_constant_pool *rcp, u_int32_t index);


#endif //TJVMSRC_RUNTIME_CONSTANT_POOL_H
