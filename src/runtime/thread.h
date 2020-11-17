//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_THREAD_H
#define TJVMSRC_THREAD_H

#include "stdlib.h"

#include "stack.h"
#include "frame.h"

struct thread {

    u_int32_t pc; // 程序计数器

    struct stack *stack; // 虚拟机栈
};

struct thread *create_thread();

void push_frame(struct thread *thread, struct frame *frame);

struct frame *pop_frame(struct thread *thread);

#endif //TJVMSRC_THREAD_H
