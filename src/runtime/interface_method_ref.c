//
// Created by tairy on 2020/11/24.
//

#include "interface_method_ref.h"

struct interface_method_ref *
new_interface_method_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp) {
    struct interface_method_ref *interface_method_ref = (struct interface_method_ref *) malloc(
            sizeof(struct interface_method_ref));
    interface_method_ref->rcp = rcp;
    interface_method_ref->classname = get_utf8(cp, (cp->infos[(int) cp_info->v1])->v1);
    get_name_and_descriptor(cp, (u_int16_t) cp_info->v2, &interface_method_ref->name,
                            &interface_method_ref->descriptor);
    return interface_method_ref;
}