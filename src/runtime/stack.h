//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_STACK_H
#define TJVMSRC_STACK_H

#include "stdlib.h"

#include "frame.h"

// 虚拟机栈结构体， Java 虚拟机规范对虚拟机栈的约束也很宽松，可以连续也可以不连续，可以固定大小，也可以在运行时扩展
struct stack {
    u_int32_t max_size;
    u_int32_t size;
    // 栈帧
    struct frame *top_frame;
};

struct stack *create_stack(u_int32_t max_size);

#endif //TJVMSRC_STACK_H
