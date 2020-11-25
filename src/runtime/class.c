//
// Created by tairy on 2020/11/17.
//

#include "class.h"
#include "field.h"
#include "method.h"
#include "runtime_constant_pool.h"
#include "access_flags.h"

struct i_klass *new_klass(struct class_loader *class_loader, struct class_file *class_file) {
    struct i_klass *clazz = (struct i_klass *) malloc(sizeof(struct i_klass));
    clazz->class_loader = class_loader;
    clazz->access_flags = class_file->access_flags;
    clazz->name = get_utf8(
            class_file->constant_pool,
            class_file->constant_pool->infos[class_file->this_class]->v1
    );
    if (strcmp(clazz->name, "java/lang/Object") != 0) {
        clazz->super_class_name = get_utf8(
                class_file->constant_pool,
                class_file->constant_pool->infos[class_file->super_class]->v1
        );
    } else {
        clazz->super_class_name = NULL;
    }
    clazz->origin_constant_pool = class_file->constant_pool;
    clazz->runtime_constant_pool = build_runtime_constant_pool(clazz->origin_constant_pool);
    clazz->fields = new_fields(clazz, class_file->fields);
    clazz->methods = new_methods(clazz, class_file->methods);
    return clazz;
}

int8_t is_class_public(struct i_klass *clazz) {
    if (((clazz->access_flags) & ACC_PUBLIC) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_class_final(struct i_klass *clazz) {
    if (((clazz->access_flags) & ACC_FINAL) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_class_protected(struct i_klass *clazz) {
    if (((clazz->access_flags) & ACC_PROTECTED) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_class_abstract(struct i_klass *clazz) {
    if (((clazz->access_flags) & ACC_ABSTRACT) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_class_static(struct i_klass *clazz) {
    if (((clazz->access_flags) & ACC_STATIC) == 0) {
        return 0;
    }
    return 1;
}