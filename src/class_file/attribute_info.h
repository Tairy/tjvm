//
// Created by tairy on 2020/11/15.
//

#ifndef TJVMSRC_ATTRIBUTE_INFO_H
#define TJVMSRC_ATTRIBUTE_INFO_H

#include "constant_pool.h"
#include "class_reader.h"
#include "string.h"

struct attribute_info {
    struct cp *cp;      // 保留文件常量池指针，后续无需再传递
    void *info;         // 属性表
};

struct attribute_infos {
    u_int32_t size;
    struct attribute_info **infos;
};

struct exception_table_entry {

    u_int16_t start_pc;

    u_int16_t end_pc;

    u_int16_t handle_pc;

    u_int16_t catch_type;
};

struct exception_table {

    u_int32_t size;

    struct exception_table_entry **entrys;

};

struct attr_code {
    u_int16_t max_stack;
    u_int16_t max_locals;
    u_int32_t code_len;

    char *code;

    struct exception_table *exception_table;

    struct attribute_infos *attributes;

};

struct marker_attribute {

};

// 定长属性
struct constant_value_attribute {

    u_int16_t constant_value_index;
};

// 方法表示
struct enclosing_method_attribute {
    u_int16_t class_index;
    u_int16_t method_index;
};

// 指向异常表
struct exceptions_attribute {
    u_int16_t len;
    u_int16_t *exception_index_table;
};

// 内部类
struct inner_class_info {
    u_int16_t inner_class_info_index;
    u_int16_t outer_class_info_index;
    u_int16_t inner_name_index;
    u_int16_t inner_class_access_flags;
};

struct inner_classes_attribute {
    u_int32_t len;
    struct inner_class_info *infos;
};

struct line_number_table_entry {
    u_int16_t start_pc;
    u_int16_t line_number;
} line_number_table_entry;

struct line_number_table_attribute {
    u_int32_t len;
    struct line_number_table_entry **entrys;
};

// 栈帧本地变量表
struct local_variable_table_entry {
    u_int16_t start_pc;
    u_int16_t length;
    u_int16_t name_index;
    u_int16_t description_index;
    u_int16_t index;
};

struct local_variable_table_attribute {
    u_int32_t len;
    struct local_variable_table_entry **entrys;
};

struct local_variable_type_table_entry {
    u_int16_t start_pc;
    u_int16_t length;
    u_int16_t name_index;
    u_int16_t signature_index;
    u_int16_t index;
};

struct local_variable_type_table_attribute {
    u_int32_t len;
    struct local_variable_type_table_entry **entry;
};

struct method_parameter {
    u_int16_t name_index;

    u_int16_t access_flags;
};

struct method_parameters {
    u_int8_t len;
    struct method_parameter **params;
};

struct signature_attribute {
    u_int16_t signature_attribute;
};

struct source_file_attribute {
    u_int16_t source_file_attribute;
};

struct unparsed_attribute {
    char *name;
    u_int32_t info_len;
    char *info;
};

static struct attribute_infos *read_attributes(struct class_reader *r, struct cp *cp);

static struct attribute_info *read_attribute(struct class_reader *r, struct cp *cp) {
    u_int16_t attr_name_index = read_uint16(r);

    char *attr_name = get_utf8(cp, attr_name_index);

    u_int32_t attr_len = read_uint32(r);
    struct attribute_info *rs = (struct attribute_info *) malloc(sizeof(struct attribute_info));
    rs->cp = cp;

    if (strcmp(attr_name, "Code") == 0) {
        struct attr_code *attr = (struct attr_code *) malloc(sizeof(struct attr_code));
        attr->max_stack = read_uint16(r);
        attr->max_locals = read_uint16(r);
        attr->code_len = read_uint32(r);
        attr->code = read_bytes(r, attr->code_len);

        u_int16_t exception_table_length = read_uint16(r);

        struct exception_table *exception_table = malloc(sizeof(struct exception_table));
        exception_table->size = exception_table_length;
        exception_table->entrys = malloc(sizeof(struct exception_table_entry *) * exception_table_length);

        for (int i = 0; i < exception_table_length; i++) {
            exception_table->entrys[i] = malloc(sizeof(struct exception_table_entry));
            exception_table->entrys[i]->start_pc = read_uint16(r);
            exception_table->entrys[i]->end_pc = read_uint16(r);
            exception_table->entrys[i]->handle_pc = read_uint16(r);
            exception_table->entrys[i]->catch_type = read_uint16(r);
        }

        attr->attributes = read_attributes(r, cp);
        rs->info = attr;
    } else if (strcmp(attr_name, "ConstantValue") == 0) {
        struct constant_value_attribute *attr = (struct constant_value_attribute *) malloc(
                sizeof(struct constant_value_attribute));
        attr->constant_value_index = read_uint16(r);
        rs->info = attr;
    } else if (strcmp(attr_name, "Deprecated") == 0) {
        struct marker_attribute *attr = (struct marker_attribute *) malloc(sizeof(struct marker_attribute));
        rs->info = attr;
    } else if (strcmp(attr_name, "Exceptions") == 0) {
        struct exceptions_attribute *attr = (struct exceptions_attribute *) malloc(sizeof(struct exceptions_attribute));
        attr->exception_index_table = read_uint16_s(r, &attr->len);
        rs->info = attr;
    } else if (strcmp(attr_name, "LineNumberTable") == 0) {
        struct line_number_table_attribute *attr = (struct line_number_table_attribute *) malloc(
                sizeof(struct line_number_table_attribute));
        attr->len = read_uint16(r);
        struct line_number_table_entry **entrys = malloc(sizeof(struct line_number_table_entry *) * attr->len);
        for (int i = 0, len = attr->len; i < len; i++) {
            entrys[i] = malloc(sizeof(struct line_number_table_entry));
            entrys[i]->start_pc = read_uint16(r);
            entrys[i]->line_number = read_uint16(r);
        }

        attr->entrys = entrys;
        rs->info = attr;
    } else if (strcmp(attr_name, "LocalVariableTable") == 0) {
        struct local_variable_table_attribute *attr = (struct local_variable_table_attribute *) malloc(
                sizeof(struct local_variable_table_attribute));
        attr->len = read_uint16(r);
        struct local_variable_table_entry **entrys = malloc(sizeof(struct local_variable_table_entry) * attr->len);
        for (int i = 0, len = attr->len; i < len; i++) {
            entrys[i]->start_pc = read_uint16(r);
            entrys[i]->length = read_uint16(r);
            entrys[i]->name_index = read_uint16(r);
            entrys[i]->description_index = read_uint16(r);
            entrys[i]->index = read_uint16(r);
        }
        attr->entrys = entrys;
        rs->info = attr;
    } else if (strcmp(attr_name, "SourceFile") == 0) {
        struct source_file_attribute *attr = (struct source_file_attribute *) malloc(
                sizeof(struct source_file_attribute));
        attr->source_file_attribute = read_uint16(r);
        rs->info = attr;
    } else if (strcmp(attr_name, "Synthetic") == 0) {
        // do nothing
        struct marker_attribute *attr = (struct marker_attribute *) malloc(sizeof(struct marker_attribute));
        rs->info = attr;
    } else if (strcmp(attr_name, "MethodParameters") == 0) {
        u_int8_t parameters_count = read_uint8(r);
        struct method_parameters *attr = (struct method_parameters *) malloc(sizeof(struct method_parameters));
        attr->len = read_uint8(r);
        struct method_parameter **parameters = malloc(sizeof(struct method_parameter) * attr->len);
        for (int i = 0, len = attr->len; i < len; i++) {
            parameters[i]->name_index = read_uint16(r);
            parameters[i]->access_flags = read_uint16(r);
        }
        attr->params = parameters;
        rs->info = attr;
    } else {
        struct unparsed_attribute *attr = (struct unparsed_attribute *) malloc(sizeof(struct unparsed_attribute));
        attr->name = attr_name;
        attr->info_len = attr_len;
        attr->info = read_bytes(r, attr_len);
    }

    return rs;
}

static struct attribute_infos *read_attributes(struct class_reader *r, struct cp *cp) {
    struct attribute_infos *rs = (struct attribute_infos *) malloc(sizeof(struct attribute_infos));
    rs->size = read_uint16(r);
    struct attribute_info **infos = malloc(sizeof(struct attribute_infos *) * rs->size);
    for (int i = 0, len = rs->size; i < len; i++) {
        infos[i] = malloc(sizeof(struct attribute_info));
        infos[i]->cp = cp;
        infos[i]->info = read_attribute(r, cp);
    }
    rs->infos = infos;
    return rs;
}

#endif //TJVMSRC_ATTRIBUTE_INFO_H
