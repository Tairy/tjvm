//
// Created by tairy on 2020/11/24.
//

#include "class_ref.h"

struct class_ref *new_class_ref(struct runtime_constant_pool *rcp, struct cp_info *cp_info, struct cp *cp) {
    // new 的时候, 不需要对 clazz 进行初始化, 后续 resolve 的时候再进行加载操作
    struct class_ref *class_ref = (struct class_ref *) malloc(sizeof(struct class_ref));
    class_ref->rcp = rcp;
    class_ref->classname = get_utf8(cp, cp_info->v1);
    return class_ref;
}

void resolve_class_ref(struct class_ref *class_ref, struct i_klass *call_clazz) {
//    if (class_ref->clazz == NULL) {
    // TODO 这里赋值的时候需要验证 call_clazz 对 class_ref->clazz 的可访问性
    // 不可访问则抛出异常

    class_ref->clazz = load_class(call_clazz->class_loader, class_ref->classname);
//    }
}
