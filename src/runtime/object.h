//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_OBJECT_H
#define TJVMSRC_OBJECT_H

#include "class.h"
#include "slot.h"

// 运行时对象结构体
struct object {
    struct i_klass *clazz;
    union slot **fields;
};

struct object *new_object(struct i_klass *clazz);

#endif //TJVMSRC_OBJECT_H
