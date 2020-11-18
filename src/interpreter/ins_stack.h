//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_STACK_H
#define TJVMSRC_INS_STACK_H

#include "runtime/frame.h"
#include "bytecode_reader.h"
#include "bytecode_interpreter.h"

void insm_87(struct frame *frame, struct bytecode_reader *reader) {
    // POP
    pop_var(frame->operand_stack);
    UPDATE_PC_AND_CONTINUE
}

void insm_88(struct frame *frame, struct bytecode_reader *reader) {
    // POP2
    pop_var(frame->operand_stack);
    pop_var(frame->operand_stack);
    UPDATE_PC_AND_CONTINUE
}

void insm_89(struct frame *frame, struct bytecode_reader *reader) {
    // DUP
    union slot *slot = pop_var(frame->operand_stack);
    push_var(frame->operand_stack, slot);
    push_var(frame->operand_stack, slot);
    UPDATE_PC_AND_CONTINUE
}

void insm_90(struct frame *frame, struct bytecode_reader *reader) {
    // DUP_X1
    union slot *x1 = pop_var(frame->operand_stack);
    union slot *x2 = pop_var(frame->operand_stack);

    push_var(frame->operand_stack, x1);
    push_var(frame->operand_stack, x2);
    push_var(frame->operand_stack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_91(struct frame *frame, struct bytecode_reader *reader) {
    // DUP_X2
    union slot *x1 = pop_var(frame->operand_stack);
    union slot *x2 = pop_var(frame->operand_stack);
    union slot *x3 = pop_var(frame->operand_stack);

    push_var(frame->operand_stack, x1);
    push_var(frame->operand_stack, x3);
    push_var(frame->operand_stack, x2);
    push_var(frame->operand_stack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_92(struct frame *frame, struct bytecode_reader *reader) {
    // DUP2
    union slot *x1 = pop_var(frame->operand_stack);
    union slot *x2 = pop_var(frame->operand_stack);

    push_var(frame->operand_stack, x2);
    push_var(frame->operand_stack, x1);
    push_var(frame->operand_stack, x2);
    push_var(frame->operand_stack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_93(struct frame *frame, struct bytecode_reader *reader) {
    // DUP2_X1
    union slot *x1 = pop_var(frame->operand_stack);
    union slot *x2 = pop_var(frame->operand_stack);
    union slot *x3 = pop_var(frame->operand_stack);

    push_var(frame->operand_stack, x2);
    push_var(frame->operand_stack, x1);
    push_var(frame->operand_stack, x3);
    push_var(frame->operand_stack, x2);
    push_var(frame->operand_stack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_94(struct frame *frame, struct bytecode_reader *reader) {
    // DUP2_X2
    union slot *x1 = pop_var(frame->operand_stack);
    union slot *x2 = pop_var(frame->operand_stack);
    union slot *x3 = pop_var(frame->operand_stack);
    union slot *x4 = pop_var(frame->operand_stack);

    push_var(frame->operand_stack, x2);
    push_var(frame->operand_stack, x1);
    push_var(frame->operand_stack, x4);
    push_var(frame->operand_stack, x3);
    push_var(frame->operand_stack, x2);
    push_var(frame->operand_stack, x1);
    UPDATE_PC_AND_CONTINUE
}

void insm_95(struct frame *frame, struct bytecode_reader *reader) {
    // SWAP
    union slot *x1 = pop_var(frame->operand_stack);
    union slot *x2 = pop_var(frame->operand_stack);

    push_var(frame->operand_stack, x1);
    push_var(frame->operand_stack, x2);
    UPDATE_PC_AND_CONTINUE
}

#endif //TJVMSRC_INS_STACK_H
