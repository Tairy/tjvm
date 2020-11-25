//
// Created by tairy on 2020/11/17.
//

#include "frame.h"
#include "local_vars.h"
#include "method.h"

struct frame *new_frame(struct thread *thread, struct method *method) {
    struct frame *frame = (struct frame *) malloc(sizeof(struct frame));
    frame->local_vars = new_local_vars(method->max_locals);
    frame->operand_stack = new_operand_stack(method->max_stack);
    frame->thread = thread;
    frame->method = method;
    frame->next_pc = 0;
    return frame;
}
