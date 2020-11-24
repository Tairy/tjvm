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
    }

    f->fields = fields;
    return f;
}

int8_t is_public(struct field *field) {

    if ((field->access_flags & ACC_PUBLIC) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_final(struct field *field) {

    if ((field->access_flags & ACC_FINAL) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_protected(struct field *field) {

    if ((field->access_flags & ACC_PROTECTED) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_static(struct field *field) {

    if ((field->access_flags & ACC_STATIC) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_synthetic(struct field *field) {

    if ((field->access_flags & ACC_SYNTHETIC) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_enum(struct field *field) {

    if ((field->access_flags & ACC_ENUM) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_volatile(struct field *field) {

    if ((field->access_flags & ACC_VOLATILE) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_transient(struct field *field) {

    if ((field->access_flags & ACC_TRANSIENT) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_long_or_double(struct field *field) {
    if (field->descriptor != "J" && field->descriptor != "D") {
        return 0;
    }

    return 1;
}
