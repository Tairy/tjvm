//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_FRAME_H
#define TJVMSRC_FRAME_H

#include "stdlib.h"

#include "thread.h"
#include "class.h"
#include "method.h"
#include "local_vars.h"
#include "operand_stack.h"

struct frame {

    struct frame *lower;

    struct local_vars *local_vars;

    struct operand_stack *operand_stack;

    // 所属线程
    struct thread *thread;

    // 当前帧所在的方法
    struct method *method;

    // 下一个执行指令位置
    int32_t next_pc;
};

struct frame *new_frame(struct thread *thread, struct method *method);

#endif //TJVMSRC_FRAME_H
