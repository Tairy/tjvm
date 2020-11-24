//
// Created by tairy on 2020/11/17.
//

#include "stdlib.h"
#include "util/util.h"
#include "class_loader.h"
#include "field.h"
#include "string.h"
#include "util/number.h"

struct i_klass *load_no_array_class(struct class_loader *class_loader, char *class_name);

struct i_klass *define_class(struct class_loader *class_loader, struct class_file *class_file);

void resolve_super_class(struct i_klass *clazz);

void resolve_interfaces(struct i_klass *clazz);

void link(struct i_klass *clazz);

void verify(struct i_klass *clazz);

void prepare(struct i_klass *clazz);

void cal_instance_field_slot_ids(struct i_klass *clazz);

void cal_static_field_slot_ids(struct i_klass *clazz);

void alloc_and_init_static_vars(struct i_klass *clazz);

void init_static_final_var(struct i_klass *clazz, struct field *field);

struct class_loader *new_class_loader(struct class_path *class_path) {
    struct class_loader *class_loader = NEW(struct class_loader);
    class_loader->class_path = class_path;
    class_loader->class_map = create_hash_map(NULL, NULL);

    return class_loader;
}

struct i_klass *load_class(struct class_loader *class_loader, char *class_name) {
    if (default_exists_func(class_loader->class_map, class_name)) {
        return default_get_func(class_loader->class_map, class_name);
    }

    return load_no_array_class(class_loader, class_name);
}

struct i_klass *load_no_array_class(struct class_loader *class_loader, char *class_name) {
    struct class_source *source = class_loader->class_path->read_class(class_loader->class_path, class_name);

    if (source == NULL) {
        return NULL;
    }
    printf("class_name: %s, len: %d\n", source->name, source->len);
    struct class_reader *reader = build_class_reader(source);
    struct class_file *class_file = read_as_class_file(reader);
    printf("file_magic: %x\n", class_file->magic);
    struct i_klass *clazz = define_class(class_loader, class_file);
    link(clazz);
    default_put_func(class_loader->class_map, class_name, clazz);
    return clazz;
}

struct i_klass *define_class(struct class_loader *class_loader, struct class_file *class_file) {
    struct i_klass *clazz = new_klass(class_loader, class_file);
    printf("access_flags: %d, class_name: %s, super_class_name: %s\n",
           clazz->access_flags,
           clazz->name,
           clazz->super_class_name
    );
    resolve_super_class(clazz);
    resolve_interfaces(clazz);
}

void resolve_super_class(struct i_klass *clazz) {
    if (strcmp(clazz->super_class_name, "java/lang/Object") != 0) {
        clazz->super_class = load_class(clazz->class_loader, clazz->super_class_name);
    }
}

void resolve_interfaces(struct i_klass *clazz) {
    // todo
}

void link(struct i_klass *clazz) {
    verify(clazz);
    prepare(clazz);
}

void verify(struct i_klass *clazz) {
    // todo
}

void prepare(struct i_klass *clazz) {
    // 给变量分配槽位、初始值化静态变量
    cal_instance_field_slot_ids(clazz);
    cal_static_field_slot_ids(clazz);
    alloc_and_init_static_vars(clazz);
}

void cal_instance_field_slot_ids(struct i_klass *clazz) {
    u_int32_t slot_index = 0;

    if (clazz->super_class != NULL) {
        slot_index = clazz->super_class->instance_slot_count;
    }

    for (int i = 0, len = clazz->fields->size; i < len; i++) {
        struct field *field = clazz->fields->fields[i];
        if (is_static(field) == 0) {
            field->slot_index = slot_index;
            slot_index++;
            if (is_long_or_double(field)) {
                slot_index++;
            }
        }
    }
    clazz->instance_slot_count = slot_index;
}

void cal_static_field_slot_ids(struct i_klass *clazz) {
    u_int32_t slot_index = 0;

    for (int i = 0, len = clazz->fields->size; i < len; i++) {
        struct field *field = clazz->fields->fields[i];
        if (is_static(field) == 1) {
            field->slot_index = slot_index;
            slot_index++;
            if (is_long_or_double(field)) {
                slot_index++;
            }
        }
    }
    clazz->static_slot_count = slot_index;
}

void alloc_and_init_static_vars(struct i_klass *clazz) {
    clazz->static_vars = malloc(sizeof(union slot) * clazz->static_slot_count);
    for (int i = 0, len = clazz->fields->size; i < len; i++) {
        struct field *field = clazz->fields->fields[i];
        if (is_static(field) == 1 && is_final(field) == 1) {
            init_static_final_var(clazz, field);
        }
    }
}

void init_static_final_var(struct i_klass *clazz, struct field *field) {
    if (field->cp_info_index > 0) {
        if (strcmp(field->descriptor, "Z") == 0 || strcmp(field->descriptor, "B") == 0 ||
            strcmp(field->descriptor, "C") == 0 || strcmp(field->descriptor, "S") == 0 ||
            strcmp(field->descriptor, "I") == 0) {
            set_int(
                    clazz->static_vars, field->slot_index,
                    clazz->origin_constant_pool->infos[field->cp_info_index]->v1
            );
        } else if (strcmp(field->descriptor, "J") == 0) {
            set_long(clazz->static_vars, field->slot_index,
                     (((int64_t) (clazz->origin_constant_pool->infos[field->cp_info_index]->v1) << 32) |
                      ((int64_t) (clazz->origin_constant_pool->infos[field->cp_info_index]->v2)))
            );
        } else if (strcmp(field->descriptor, "F") == 0) {
            set_float(clazz->static_vars, field->slot_index,
                      int_bits_to_float((int) (clazz->origin_constant_pool->infos[field->cp_info_index]->v1)));
        } else if (strcmp(field->descriptor, "D") == 0) {
            set_double(clazz->static_vars, field->slot_index, int_bits_to_double(
                    (((int64_t) (clazz->origin_constant_pool->infos[field->cp_info_index]->v1) << 32) |
                     ((int64_t) (clazz->origin_constant_pool->infos[field->cp_info_index]->v2)))
            ));
        } else if (strcmp(field->descriptor, "Ljava/lang/String;")) {
            // todo
        }
    }
}

