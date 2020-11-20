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

struct field {
    struct i_klass *clazz;
    u_int16_t access_flags;
    char *name;
    char *descriptor;
    // 属性初始化值
    u_int32_t rcp_info_index;
    // 属性存储位置
    u_int32_t slot_index;
};

struct fields {
    u_int32_t size;
    struct field **fields;
};

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
    union slot *static_vars;
};

// instanceMirrorClass => java.lang.class
struct im_klass {
    struct i_klass *clazz;
};

struct i_klass *new_klass(struct class_file *class_file);

struct fields *new_fields(struct i_klass *clazz, struct member_infos *fields);

struct methods *new_methods(struct i_klass *clazz, struct member_infos *origin_methods);

#endif //TJVMSRC_CLASS_H
