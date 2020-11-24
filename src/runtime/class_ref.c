//
// Created by tairy on 2020/11/24.
//

#include "class_ref.h"

struct class_ref *new_class_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp) {
    struct class_ref *class_ref = (struct class_ref *) malloc(sizeof(struct class_ref));
    class_ref->rcp = rcp;
    class_ref->classname = get_utf8(cp, (cp->infos[(int) cp_info->v1])->v1);
    return class_ref;
}