//
// Created by tairy on 2020/11/24.
//

#include "class.h"
#include "field.h"
#include "access_flags.h"
#include "class_file/constant_pool.h"

struct fields *new_fields(struct i_klass *clazz, struct member_infos *origin_fields) {
    struct fields *f = (struct fields *) malloc(sizeof(struct fields));
    f->size = origin_fields->size;
    struct field **fields = malloc(sizeof(struct field *) * f->size);
    for (int i = 0, len = f->size; i < len; i++) {
        fields[i] = malloc(sizeof(struct field));
        fields[i]->clazz = clazz;
        fields[i]->access_flags = origin_fields->infos[i]->access_flags;
        fields[i]->name = get_utf8(clazz->origin_constant_pool, origin_fields->infos[i]->name_index);
        fields[i]->descriptor = get_utf8(clazz->origin_constant_pool, origin_fields->infos[i]->description_index);

        if (origin_fields->infos[i]->attributes->size > 0) {
            for (int j = 0; j < origin_fields->infos[i]->attributes->size; j++) {
                char *attr_name = get_utf8(clazz->origin_constant_pool,
                                           origin_fields->infos[i]->attributes->infos[j]->attribute_index);

                if (strcmp(attr_name, "ConstantValue") == 0) {
                    struct constant_value_attribute *attr = origin_fields->infos[i]->attributes->infos[j]->info;
                    fields[i]->cp_info_index = attr->constant_value_index;
                }
            }
        }
    }

    f->fields = fields;
    return f;
}

int8_t is_field_public(struct field *field) {

    if (((field->access_flags) & ACC_PUBLIC) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_field_final(struct field *field) {

    if (((field->access_flags) & ACC_FINAL) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_field_protected(struct field *field) {

    if (((field->access_flags) & ACC_PROTECTED) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_field_static(struct field *field) {

    if (((field->access_flags) & ACC_STATIC) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_field_synthetic(struct field *field) {

    if (((field->access_flags) & ACC_SYNTHETIC) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_field_enum(struct field *field) {

    if (((field->access_flags) & ACC_ENUM) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_field_volatile(struct field *field) {

    if (((field->access_flags) & ACC_VOLATILE) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_field_transient(struct field *field) {

    if (((field->access_flags) & ACC_TRANSIENT) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_field_long_or_double(struct field *field) {
    if (strcmp(field->descriptor, "J") != 0 && strcmp(field->descriptor, "D") != 0) {
        return 0;
    }

    return 1;
}
