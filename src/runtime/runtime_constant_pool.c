//
// Created by tairy on 2020/11/20.
//

#include "runtime_constant_pool.h"

struct runtime_constant_pool *build_runtime_constant_pool(struct class_file *class_file) {
    struct cp *cp = class_file->constant_pool;

    // 运行时类
    struct i_klass *clazz = new_klass(class_file);
    struct runtime_constant_pool *rcp = (struct runtime_constant_pool *) malloc(sizeof(struct runtime_constant_pool));
    clazz->runtime_constant_pool = rcp;
    rcp->size = cp->len;
    struct runtime_constant_pool_info **infos = malloc(sizeof(struct runtime_constant_pool_info *) * rcp->size);
    for (int i = 0, size = rcp->size; i < size; i++) {
        infos[i] = (struct runtime_constant_pool_info *) malloc(sizeof(struct runtime_constant_pool_info));
        infos[i]->type = cp->infos[i]->tag;

        switch (cp->infos[i]->tag) {
            case CONSTANT_Integer_info:
            case CONSTANT_Float_info:
            case CONSTANT_String_info:
                infos[i]->data = cp->infos[i]->v1;
                break;
            case CONSTANT_Long_info:
            case CONSTANT_Double_info:
                infos[i]->data = (u_int64_t) (cp->infos[i]->v1) << 32 | (u_int64_t) cp->infos[i]->v2;
                i++;
                break;
            case CONSTANT_Class_info:
                infos[i]->data = new_class_ref(rcp, clazz);
                break;
            case CONSTANT_Field_ref_info:
                infos[i]->data = new_field_ref(rcp);
                break;
            case CONSTANT_Method_ref_info:
                infos[i]->data = new_method_ref(rcp);
                break;
            case CONSTANT_Interface_Method_ref_info:
                infos[i]->data = new_interface_method_ref(rcp);
                break;
        }
    }

    rcp->infos = infos;
    return rcp;
}

struct runtime_constant_pool_info *
get_runtime_constant_pool_info(struct runtime_constant_pool *rcp, u_int32_t index) {
    return rcp->infos[index];
}

struct class_ref *new_class_ref(struct runtime_constant_pool *rcp, struct i_klass *clazz) {
    struct class_ref *class_ref = (struct class_ref *) malloc(sizeof(struct class_ref));
    class_ref->rcp = rcp;
    class_ref->classname = clazz->name;
    return class_ref;
}

struct field_ref *new_field_ref(struct runtime_constant_pool *rcp) {
    struct field_ref *field_ref = (struct field_ref *) malloc(sizeof(struct field_ref));
    field_ref->rcp = rcp;

    return field_ref;
}

struct method_ref *new_method_ref(struct runtime_constant_pool *rcp) {
    struct method_ref *method_ref = (struct method_ref *) malloc(sizeof(struct method_ref));
    method_ref->rcp = rcp;
    return method_ref;
}

struct interface_method_ref *new_interface_method_ref(struct runtime_constant_pool *rcp) {
    struct interface_method_ref *interface_method_ref = (struct interface_method_ref *) malloc(
            sizeof(struct interface_method_ref));
    interface_method_ref->rcp = rcp;
    return interface_method_ref;
}
