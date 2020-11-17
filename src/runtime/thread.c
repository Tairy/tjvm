//
// Created by tairy on 2020/11/17.
//

#include "thread.h"
#include "stack.h"

#include "util/log.h"

struct thread *create_thread() {
    struct thread *thread = malloc(sizeof(struct thread));
    thread->pc = 0;

    // 虚拟机栈
    thread->stack = create_stack(1024);
    return thread;
}

void push_frame(struct thread *thread, struct frame *frame) {
    if (thread->stack->size > thread->stack->max_size) {
        log_error(__FILE__, __LINE__, "java.lang.StackOverflowError.");
        return;
    }

    if (thread->stack->top_frame != NULL) {
        frame->lower = thread->stack->top_frame;
    }

    thread->stack->top_frame = frame;

    thread->stack->size++;
}

struct frame *pop_frame(struct thread *thread) {
    if (thread->stack->top_frame == NULL) {
        log_error(__FILE__, __LINE__, "jvm stack is empty.");
        exit(1);
    }

    struct frame *top_frame = thread->stack->top_frame;
    thread->stack->top_frame = top_frame->lower;
    top_frame->lower = NULL;
    thread->stack->size--;
    return top_frame;
}

struct frame *top_frame(struct thread *thread) {
    return thread->stack->top_frame;
}

struct frame *current_frame(struct thread *thread) {

}