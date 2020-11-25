//
// Created by tairy on 2020/11/24.
//

#include "method.h"
#include "class_file/member_info.h"
#include "access_flags.h"
#include "method_descriptor_parser.h"
#include "method_descriptor.h"
#include "string.h"

u_int32_t calc_arg_slot_count(struct method *method);

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
        methods[i]->arg_count = calc_arg_slot_count(methods[i]);

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

u_int32_t calc_arg_slot_count(struct method *method) {
    struct method_descriptor *method_descriptor = parse_method_descriptor(method->descriptor);
    u_int32_t slot_count = 0;

    for (int i = 0; i < method_descriptor->param_size; i++) {
        slot_count++;
        if (strcmp(method_descriptor->param_types[i], "J") == 0 ||
            strcmp(method_descriptor->param_types[i], "D") == 0) {
            slot_count++;
        }
    }

    if (is_method_static(method) == 0) {
        slot_count++;
    }

    return slot_count;
}

int8_t is_method_public(struct method *method) {
    if (((method->access_flags) & ACC_PUBLIC) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_method_final(struct method *method) {
    if (((method->access_flags) & ACC_FINAL) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_method_protected(struct method *method) {
    if (((method->access_flags) & ACC_PROTECTED) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_method_abstract(struct method *method) {
    if (((method->access_flags) & ACC_ABSTRACT) == 0) {
        return 0;
    }
    return 1;
}

int8_t is_method_static(struct method *method) {
    if (((method->access_flags) & ACC_STATIC) == 0) {
        return 0;
    }
    return 1;
}