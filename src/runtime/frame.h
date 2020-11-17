//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_FRAME_H
#define TJVMSRC_FRAME_H

#include "stdlib.h"
#include "local_vars.h"
#include "operand_stack.h"

struct frame {

    struct frame *lower;

    struct local_vars *local_vars;

    struct operand_stack *operand_stack;
};

struct frame *new_frame(u_int32_t max_locals, u_int32_t max_stack);

#endif //TJVMSRC_FRAME_H
