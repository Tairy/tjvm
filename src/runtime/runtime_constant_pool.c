//
// Created by tairy on 2020/11/20.
//

#include "runtime_constant_pool.h"

struct runtime_constant_pool *build_runtime_constant_pool(struct class_loader *class_loader, struct cp *cp) {
    struct runtime_constant_pool *rcp = (struct runtime_constant_pool *) malloc(sizeof(struct runtime_constant_pool));
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
                infos[i]->data = ((u_int64_t) (cp->infos[i]->v1)) << 32 | ((u_int64_t) cp->infos[i]->v2);
                i++;
                break;
            case CONSTANT_Class_info:
                infos[i]->data = new_class_ref(rcp, cp->infos[i], cp, class_loader);
                break;
            case CONSTANT_Field_ref_info:
                infos[i]->data = new_field_ref(rcp, cp->infos[i], cp, class_loader);
                break;
            case CONSTANT_Method_ref_info:
                infos[i]->data = new_method_ref(rcp, cp->infos[i], cp, class_loader);
                break;
            case CONSTANT_Interface_Method_ref_info:
                infos[i]->data = new_interface_method_ref(rcp, cp->infos[i], cp, class_loader);
                break;
        }
    }

    rcp->infos = infos;
    return rcp;
}

struct runtime_constant_pool_info *get_runtime_constant_pool_info(struct runtime_constant_pool *rcp, u_int32_t index) {
    return rcp->infos[index];
}

struct class_ref *new_class_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp,
                                struct class_loader *class_loader) {
    struct class_ref *class_ref = (struct class_ref *) malloc(sizeof(struct class_ref));
    class_ref->rcp = rcp;
    class_ref->classname = get_utf8(cp, (cp->infos[(int) cp_info->v1])->v1);
    class_ref->clazz = load_class(class_loader, class_ref->classname);
    return class_ref;
}

static inline void get_name_and_descriptor(struct cp *cp, u_int16_t index, char **name, char **descriptor) {
    struct cp_info *name_and_type = cp->infos[index];
    *name = (char *) (cp->infos[(u_int16_t) name_and_type->v1])->v2;
    *descriptor = (char *) (cp->infos[(u_int16_t) name_and_type->v2])->v2;
}

struct field_ref *new_field_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp,
                                struct class_loader *class_loader) {
    struct field_ref *field_ref = (struct field_ref *) malloc(sizeof(struct field_ref));
    field_ref->rcp = rcp;
    field_ref->classname = get_utf8(cp, (cp->infos[(int) cp_info->v1])->v1);
    field_ref->clazz = load_class(class_loader, field_ref->classname);
    get_name_and_descriptor(cp, (u_int16_t) cp_info->v2, &field_ref->name, &field_ref->descriptor);
    return field_ref;
}

struct method_ref *
new_method_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp,
               struct class_loader *class_loader) {
    struct method_ref *method_ref = (struct method_ref *) malloc(sizeof(struct method_ref));
    method_ref->rcp = rcp;
    method_ref->classname = get_utf8(cp, (cp->infos[(int) cp_info->v1])->v1);
    method_ref->clazz = load_class(class_loader, method_ref->classname);
    get_name_and_descriptor(cp, (u_int16_t) cp_info->v2, &method_ref->name, &method_ref->descriptor);
    return method_ref;
}

struct interface_method_ref *
new_interface_method_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp,
                         struct class_loader *class_loader) {
    struct interface_method_ref *interface_method_ref = (struct interface_method_ref *) malloc(
            sizeof(struct interface_method_ref));
    interface_method_ref->rcp = rcp;
    interface_method_ref->classname = get_utf8(cp, (cp->infos[(int) cp_info->v1])->v1);
    interface_method_ref->clazz = load_class(class_loader, interface_method_ref->classname);
    get_name_and_descriptor(cp, (u_int16_t) cp_info->v2, &interface_method_ref->name,
                            &interface_method_ref->descriptor);
    return interface_method_ref;
}
