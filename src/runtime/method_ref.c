//
// Created by tairy on 2020/11/24.
//

#include "method_ref.h"

struct method_ref *new_method_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp) {
    struct method_ref *method_ref = (struct method_ref *) malloc(sizeof(struct method_ref));
    method_ref->rcp = rcp;
    method_ref->classname = get_utf8(cp, (cp->infos[(int) cp_info->v1])->v1);
    get_name_and_descriptor(cp, (u_int16_t) cp_info->v2, &method_ref->name, &method_ref->descriptor);
    return method_ref;
}

struct method *look_up_method(struct i_klass *clazz, char *name, char *descriptor);

struct method *look_up_method_in_class(struct i_klass *clazz, char *name, char *descriptor);

struct method *look_up_method_in_interfaces();

void resolve_method_ref(struct method_ref *method_ref, struct i_klass *call_clazz) {
    // TODO 这里赋值的时候需要验证 call_clazz 对 method_ref->method 的可访问性
    // 不可访问则抛出异常

    method_ref->clazz = load_class(call_clazz->class_loader, method_ref->classname);
    method_ref->method = look_up_method(method_ref->clazz, method_ref->name, method_ref->descriptor);
}

struct method *look_up_method(struct i_klass *clazz, char *name, char *descriptor) {
    struct method *method = look_up_method_in_class(clazz, name, descriptor);

    if (method == NULL) {
        return look_up_method_in_interfaces();
    }

    return method;
}

struct method *look_up_method_in_class(struct i_klass *clazz, char *name, char *descriptor) {
    for (struct i_klass *c = clazz; c != NULL; c = c->super_class) {
        for (int i = 0; i < clazz->methods->size; i++) {
            struct method *method = clazz->methods->methods[i];
            if (strcmp(method->name, name) == 0 && strcmp(method->descriptor, descriptor) == 0) {
                return method;
            }
        }
    }

    return NULL;
}

struct method *look_up_method_in_interfaces() {
    // TODO: interface
}

