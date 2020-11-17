//
// Created by tairy on 2020/11/17.
//

#include "frame.h"
#include "local_vars.h"

struct frame *new_frame(u_int32_t max_locals, u_int32_t max_stack) {
    struct frame *frame = (struct frame *) malloc(sizeof(struct frame));
    frame->local_vars = new_local_vars(max_locals);
    frame->operand_stack = new_operand_stack(max_stack);
    return frame;
}
