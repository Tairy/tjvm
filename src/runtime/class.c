//
// Created by tairy on 2020/11/17.
//

#include "class.h"
#include "runtime_constant_pool.h"

struct i_klass *new_klass(struct class_file *class_file) {
    struct i_klass *clazz = (struct i_klass *) malloc(sizeof(struct i_klass));
    clazz->access_flags = class_file->access_flags;
    clazz->name = get_utf8(
            class_file->constant_pool,
            class_file->constant_pool->infos[class_file->this_class]->v1
    );
    clazz->super_class_name = get_utf8(
            class_file->constant_pool,
            class_file->constant_pool->infos[class_file->super_class]->v1
    );
    clazz->runtime_constant_pool = build_runtime_constant_pool(class_file->constant_pool);
    clazz->origin_constant_pool = class_file->constant_pool;
    clazz->fields = new_fields(clazz, class_file->fields);
    clazz->methods = new_methods(clazz, class_file->methods);
    return clazz;
}

struct fields *new_fields(struct i_klass *clazz, struct member_infos *origin_fields) {
    struct fields *f = (struct fields *) malloc(sizeof(struct fields));
    f->size = origin_fields->size;
    struct field **fields = malloc(sizeof(struct field *) * f->size);
    for (int i = 0, len = f->size; i < len; i++) {
        fields[i] = malloc(sizeof(struct field));
        fields[i]->clazz = clazz;
        fields[i]->access_flags = origin_fields->infos[i]->access_flags;
        fields[i]->name = get_utf8(clazz->origin_constant_pool, origin_fields->infos[i]->name_index);
    }

    f->fields = fields;
    return f;
}

struct methods *new_methods(struct i_klass *clazz, struct member_infos *origin_methods) {
    struct methods *m = (struct methods *) malloc(sizeof(struct methods));
    m->size = origin_methods->size;
    struct method **methods = malloc(sizeof(struct method *) * m->size);

    for (int i = 0, len = m->size; i < len; i++) {
        struct member_info *current_member_info = origin_methods->infos[i];
        methods[i] = malloc(sizeof(struct method));
        methods[i]->clazz = clazz;
        methods[i]->access_flags = current_member_info->access_flags;
        methods[i]->name = get_utf8(clazz->origin_constant_pool, current_member_info->name_index);
        methods[i]->descriptor = get_utf8(clazz->origin_constant_pool, current_member_info->description_index);

        for (int j = 0; j < current_member_info->attributes->size; j++) {
            char *attr_name = get_utf8(clazz->origin_constant_pool,
                                       current_member_info->attributes->infos[j]->attribute_index);

            if (strcmp(attr_name, "Code") == 0) {
                struct attr_code *attr_code = ((struct attr_code *) (current_member_info->attributes->infos[j]->info));
                methods[i]->max_stack = attr_code->max_stack;
                methods[i]->max_locals = attr_code->max_locals;
                methods[i]->code = attr_code->code;
                methods[i]->code_len = attr_code->code_len;
            }
        }
    }

    m->methods = methods;
    return m;
}