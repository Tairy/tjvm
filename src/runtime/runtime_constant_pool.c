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
                infos[i]->data = new_class_ref(rcp, cp->infos[i], cp);
                break;
            case CONSTANT_Field_ref_info:
                infos[i]->data = new_field_ref(rcp, cp->infos[i], cp);
                break;
            case CONSTANT_Method_ref_info:
                infos[i]->data = new_method_ref(rcp, cp->infos[i], cp);
                break;
            case CONSTANT_Interface_Method_ref_info:
                infos[i]->data = new_interface_method_ref(rcp, cp->infos[i], cp);
                break;
        }
    }

    rcp->infos = infos;
    return rcp;
}

struct runtime_constant_pool_info *get_runtime_constant_pool_info(struct runtime_constant_pool *rcp, u_int32_t index) {
    return rcp->infos[index];
}

static void get_name_and_descriptor(struct cp *cp, u_int16_t index, char **name, char **descriptor) {
    struct cp_info *name_and_type = cp->infos[index];
    *name = (char *) (cp->infos[(u_int16_t) name_and_type->v1])->v2;
    *descriptor = (char *) (cp->infos[(u_int16_t) name_and_type->v2])->v2;
}
