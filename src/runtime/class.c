//
// Created by tairy on 2020/11/17.
//

#include "class.h"

struct i_klass *new_klass(struct class_file *class_file) {
    struct i_klass *clazz = (struct i_klass *) malloc(sizeof(struct i_klass));
    clazz->access_flags = class_file->access_flags;
    clazz->name = get_utf8(class_file->constant_pool, class_file->constant_pool->infos[class_file->this_class]->v1);
    return clazz;
}