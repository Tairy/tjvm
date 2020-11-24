//
// Created by tairy on 2020/11/24.
//

#include "field_ref.h"

struct field_ref *new_field_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp) {
    struct field_ref *field_ref = (struct field_ref *) malloc(sizeof(struct field_ref));
    field_ref->rcp = rcp;
    field_ref->classname = get_utf8(cp, (cp->infos[(int) cp_info->v1])->v1);
    get_name_and_descriptor(cp, (u_int16_t) cp_info->v2, &field_ref->name, &field_ref->descriptor);
    return field_ref;
}