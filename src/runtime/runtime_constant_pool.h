//
// Created by tairy on 2020/11/17.
//
// 运行时常量池，类加载时解析

#ifndef TJVMSRC_RUNTIME_CONSTANT_POOL_H
#define TJVMSRC_RUNTIME_CONSTANT_POOL_H

#include "class_file/constant_pool.h"
#include "runtime/class.h"

struct class_ref {
    char *classname;
};

struct member_ref {
    char *classname;
    char *name;
    char *descriptor;
};

//struct cp_info {
//    u_int8_t tag;
//    void *v1;
//    void *v2;
//};

struct runtime_constant_pool_info {
    u_int8_t type;
    void *data;
};

struct runtime_constant_pool {
    u_int32_t size;

    struct runtime_constant_pool_info **infos;
};

static struct runtime_constant_pool *build_runtime_constant_pool(struct cp *cp) {
    struct runtime_constant_pool *rcp = (struct runtime_constant_pool *) malloc(sizeof(struct runtime_constant_pool));
    rcp->size = cp->len;
    struct runtime_constant_pool_info **infos = malloc(sizeof(struct runtime_constant_pool_info *) * rcp->size);
    for (int i = 0, size = rcp->size; i < size; i++) {
        infos[i] = (struct runtime_constant_pool_info *) malloc(sizeof(struct runtime_constant_pool_info));
        infos[i]->type = cp->infos[i]->tag;
        if (cp->infos[i]->tag == CONSTANT_Double_info || cp->infos[i]->tag == CONSTANT_Long_info) {
            i++;
        }
    }

    rcp->infos = infos;
    return rcp;
}

static struct runtime_constant_pool_info *
get_runtime_constant_pool_info(struct runtime_constant_pool *rcp, u_int32_t index) {
    return rcp->infos[index];
}

#endif //TJVMSRC_RUNTIME_CONSTANT_POOL_H
