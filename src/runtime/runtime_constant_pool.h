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
#include "class_ref.h"
#include "field_ref.h"
#include "method_ref.h"
#include "interface_method_ref.h"

struct runtime_constant_pool_info {
    u_int8_t type;
    void *data;
};

struct runtime_constant_pool {
    u_int32_t size;
    struct runtime_constant_pool_info **infos;
};

static void get_name_and_descriptor(struct cp *cp, u_int16_t index, char **name, char **descriptor);

struct runtime_constant_pool *build_runtime_constant_pool(struct class_loader *class_loader, struct cp *cp);

struct runtime_constant_pool_info *get_runtime_constant_pool_info(struct runtime_constant_pool *rcp, u_int32_t index);


#endif //TJVMSRC_RUNTIME_CONSTANT_POOL_H
