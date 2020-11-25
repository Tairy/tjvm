//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_LOAD_H
#define TJVMSRC_INS_LOAD_H

#include <stdint.h>
#include "runtime/frame.h"
#include "bytecode_reader.h"
#include "bytecode_interpreter.h"
// 加载指令

void insm_21(struct frame *frame, struct bytecode_reader *reader) {
    // ILOAD    21  0x15 将指定的 int 型局部变量推送至栈顶
    push_int(frame->operand_stack, get_int(frame->local_vars->vars, next_int8(reader)));
    UPDATE_PC_AND_CONTINUE
}

void insm_22(struct frame *frame, struct bytecode_reader *reader) {
    // LLOAD    22  0x16 将指定的 long 型局部变量推送至栈顶
    push_long(frame->operand_stack, get_long(frame->local_vars->vars, next_int8(reader)));
    UPDATE_PC_AND_CONTINUE
}

void insm_23(struct frame *frame, struct bytecode_reader *reader) {
    // FLOAD
    push_float(frame->operand_stack, get_float(frame->local_vars->vars, next_int8(reader)));
    UPDATE_PC_AND_CONTINUE
}

void insm_24(struct frame *frame, struct bytecode_reader *reader) {
    // DLOAD
    push_double(frame->operand_stack, get_double(frame->local_vars->vars, next_int8(reader)));
    UPDATE_PC_AND_CONTINUE
}

void insm_25(struct frame *frame, struct bytecode_reader *reader) {
    // ALOAD
    push_ref(frame->operand_stack, get_ref(frame->local_vars->vars, next_int8(reader)));
    UPDATE_PC_AND_CONTINUE
}

void insm_26(struct frame *frame, struct bytecode_reader *reader) {
    // ILOAD_0 将第一个 int 型局部变量推送至栈顶
    push_int(frame->operand_stack, get_int(frame->local_vars->vars, 0));
    UPDATE_PC_AND_CONTINUE
}

void insm_27(struct frame *frame, struct bytecode_reader *reader) {
    // ILOAD_1
    push_int(frame->operand_stack, get_int(frame->local_vars->vars, 1));
    UPDATE_PC_AND_CONTINUE
}

void insm_28(struct frame *frame, struct bytecode_reader *reader) {
    // ILOAD_2
    push_int(frame->operand_stack, get_int(frame->local_vars->vars, 2));
    UPDATE_PC_AND_CONTINUE
}

void insm_29(struct frame *frame, struct bytecode_reader *reader) {
    // ILOAD_3
    push_int(frame->operand_stack, get_int(frame->local_vars->vars, 3));
    UPDATE_PC_AND_CONTINUE
}

void insm_30(struct frame *frame, struct bytecode_reader *reader) {
    // LLOAD_0
    push_long(frame->operand_stack, get_long(frame->local_vars->vars, 0));
    UPDATE_PC_AND_CONTINUE
}

void insm_31(struct frame *frame, struct bytecode_reader *reader) {
    push_long(frame->operand_stack, get_long(frame->local_vars->vars, 1));
    UPDATE_PC_AND_CONTINUE
}

void insm_32(struct frame *frame, struct bytecode_reader *reader) {
    push_long(frame->operand_stack, get_long(frame->local_vars->vars, 2));
    UPDATE_PC_AND_CONTINUE
}

void insm_33(struct frame *frame, struct bytecode_reader *reader) {
    // lload_3
    push_long(frame->operand_stack, get_long(frame->local_vars->vars, 3));
    UPDATE_PC_AND_CONTINUE
}

void insm_34(struct frame *frame, struct bytecode_reader *reader) {
    push_float(frame->operand_stack, get_float(frame->local_vars->vars, 0));
    UPDATE_PC_AND_CONTINUE
}

void insm_35(struct frame *frame, struct bytecode_reader *reader) {
    push_float(frame->operand_stack, get_float(frame->local_vars->vars, 1));
    UPDATE_PC_AND_CONTINUE
}

void insm_36(struct frame *frame, struct bytecode_reader *reader) {
    push_float(frame->operand_stack, get_float(frame->local_vars->vars, 2));
    UPDATE_PC_AND_CONTINUE
}

void insm_37(struct frame *frame, struct bytecode_reader *reader) {
    push_float(frame->operand_stack, get_float(frame->local_vars->vars, 3));
    UPDATE_PC_AND_CONTINUE
}

void insm_38(struct frame *frame, struct bytecode_reader *reader) {
    push_double(frame->operand_stack, get_double(frame->local_vars->vars, 0));
    UPDATE_PC_AND_CONTINUE
}

void insm_39(struct frame *frame, struct bytecode_reader *reader) {
    push_double(frame->operand_stack, get_double(frame->local_vars->vars, 1));
    UPDATE_PC_AND_CONTINUE
}

void insm_40(struct frame *frame, struct bytecode_reader *reader) {
    push_double(frame->operand_stack, get_double(frame->local_vars->vars, 2));
    UPDATE_PC_AND_CONTINUE
}

void insm_41(struct frame *frame, struct bytecode_reader *reader) {
    push_double(frame->operand_stack, get_double(frame->local_vars->vars, 3));
    UPDATE_PC_AND_CONTINUE
}

void insm_42(struct frame *frame, struct bytecode_reader *reader) {
    // ALOAD_0
    push_ref(frame->operand_stack, get_ref(frame->local_vars->vars, 0));
    UPDATE_PC_AND_CONTINUE
}

void insm_43(struct frame *frame, struct bytecode_reader *reader) {
    push_ref(frame->operand_stack, get_ref(frame->local_vars->vars, 1));
    UPDATE_PC_AND_CONTINUE
}

void insm_44(struct frame *frame, struct bytecode_reader *reader) {
    push_ref(frame->operand_stack, get_ref(frame->local_vars->vars, 2));
    UPDATE_PC_AND_CONTINUE
}

void insm_45(struct frame *frame, struct bytecode_reader *reader) {
    push_ref(frame->operand_stack, get_ref(frame->local_vars->vars, 3));
    UPDATE_PC_AND_CONTINUE
}

void insm_46(struct frame *frame, struct bytecode_reader *reader) {}

void insm_47(struct frame *frame, struct bytecode_reader *reader) {}

void insm_48(struct frame *frame, struct bytecode_reader *reader) {}

void insm_49(struct frame *frame, struct bytecode_reader *reader) {}

void insm_50(struct frame *frame, struct bytecode_reader *reader) {}

void insm_51(struct frame *frame, struct bytecode_reader *reader) {}

void insm_52(struct frame *frame, struct bytecode_reader *reader) {}

void insm_53(struct frame *frame, struct bytecode_reader *reader) {}

#endif //TJVMSRC_INS_LOAD_H
