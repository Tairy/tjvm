//
// Created by tairy on 2020/11/24.
//

#include "method_ref.h"

struct method_ref *
new_method_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp) {
    struct method_ref *method_ref = (struct method_ref *) malloc(sizeof(struct method_ref));
    method_ref->rcp = rcp;
    method_ref->classname = get_utf8(cp, (cp->infos[(int) cp_info->v1])->v1);
    get_name_and_descriptor(cp, (u_int16_t) cp_info->v2, &method_ref->name, &method_ref->descriptor);
    return method_ref;
}