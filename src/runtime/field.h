//
// Created by tairy on 2020/11/24.
//

#ifndef TJVMSRC_FIELD_H
#define TJVMSRC_FIELD_H

#include "stdlib.h"
#include "class_file/member_info.h"

struct field {

    struct i_klass *clazz;

    u_int16_t access_flags;

    char *name;

    char *descriptor;
    // 静态变量属性初始化值
    u_int32_t cp_info_index;
    // 属性存储位置
    u_int32_t slot_index;
};

struct fields {

    u_int32_t size;

    struct field **fields;
};

struct fields *new_fields(struct i_klass *clazz, struct member_infos *fields);

int8_t is_field_public(struct field *field);

int8_t is_field_final(struct field *field);

int8_t is_field_protected(struct field *field);

int8_t is_field_abstract(struct field *field);

int8_t is_field_static(struct field *field);

int8_t is_field_synthetic(struct field *field);

int8_t is_field_enum(struct field *field);

int8_t is_field_volatile(struct field *field);

int8_t is_field_transient(struct field *field);

int8_t is_field_long_or_double(struct field *field);


#endif //TJVMSRC_FIELD_H
