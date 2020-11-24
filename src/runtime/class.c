//
// Created by tairy on 2020/11/17.
//

#include "class.h"
#include "field.h"
#include "method.h"
#include "runtime_constant_pool.h"

struct i_klass *new_klass(struct class_loader *class_loader, struct class_file *class_file) {
    struct i_klass *clazz = (struct i_klass *) malloc(sizeof(struct i_klass));
    clazz->class_loader = class_loader;
    clazz->access_flags = class_file->access_flags;
    clazz->name = get_utf8(
            class_file->constant_pool,
            class_file->constant_pool->infos[class_file->this_class]->v1
    );
    clazz->super_class_name = get_utf8(
            class_file->constant_pool,
            class_file->constant_pool->infos[class_file->super_class]->v1
    );
    clazz->origin_constant_pool = class_file->constant_pool;

    // todo 运行时常量池的作用有待继续深入理解
    clazz->runtime_constant_pool = build_runtime_constant_pool(class_loader, clazz->origin_constant_pool);
    clazz->fields = new_fields(clazz, class_file->fields);
    clazz->methods = new_methods(clazz, class_file->methods);
    return clazz;
}