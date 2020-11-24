//
// Created by tairy on 2020/11/17.
//

#include "object.h"

struct object *new_object(struct i_klass *clazz) {
    struct object *object = (struct object *) malloc(sizeof(struct object));
    object->clazz = clazz;
    object->fields = malloc(sizeof(union slot) * clazz->instance_slot_count);

    return object;
}
