//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_CLASS_H
#define TJVMSRC_CLASS_H

#include "stdlib.h"
#include "slot.h"
#include "runtime_constant_pool.h"
#include "class_file/class_file.h"
#include "class_file/member_info.h"
#include "class_file/constant_pool.h"
#include "class_loader.h"

struct interfaces {
    u_int32_t size;
    void *clazz_array;
};

struct i_klass {
    u_int16_t access_flags;
    char *name;
    char *super_class_name;
    struct interfaces *interfaces;
    struct runtime_constant_pool *runtime_constant_pool;
    struct cp *origin_constant_pool; // TODO 临时指向原始常量池，后续再做优化
    struct class_loader *class_loader;
    struct fields *fields;
    struct methods *methods;
    struct i_klass *super_class;

    u_int32_t instance_slot_count;
    u_int32_t static_slot_count;
    union slot **static_vars;
};

// instanceMirrorClass => java.lang.class
struct im_klass {
    struct i_klass *clazz;
};

struct i_klass *new_klass(struct class_loader *class_loader, struct class_file *class_file);

#endif //TJVMSRC_CLASS_H
