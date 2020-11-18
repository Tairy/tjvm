//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_CONVERT_H
#define TJVMSRC_INS_CONVERT_H

#include "runtime/frame.h"
#include "bytecode_reader.h"
#include "bytecode_interpreter.h"

void insm_133(struct frame *frame, struct bytecode_reader *reader) {
    // I2L
    int32_t x = pop_int(frame->operand_stack);
    push_long(frame->operand_stack, (int64_t) x);
    UPDATE_PC_AND_CONTINUE
}

void insm_134(struct frame *frame, struct bytecode_reader *reader) {}

void insm_135(struct frame *frame, struct bytecode_reader *reader) {}

void insm_136(struct frame *frame, struct bytecode_reader *reader) {}

void insm_137(struct frame *frame, struct bytecode_reader *reader) {}

void insm_138(struct frame *frame, struct bytecode_reader *reader) {}

void insm_139(struct frame *frame, struct bytecode_reader *reader) {}

void insm_140(struct frame *frame, struct bytecode_reader *reader) {}

void insm_141(struct frame *frame, struct bytecode_reader *reader) {}

void insm_142(struct frame *frame, struct bytecode_reader *reader) {}

void insm_143(struct frame *frame, struct bytecode_reader *reader) {
    // D2L
    double x = pop_double(frame->operand_stack);
    push_long(frame->operand_stack, (int64_t) x);
    UPDATE_PC_AND_CONTINUE
}

void insm_144(struct frame *frame, struct bytecode_reader *reader) {}

void insm_145(struct frame *frame, struct bytecode_reader *reader) {}

void insm_146(struct frame *frame, struct bytecode_reader *reader) {}

void insm_147(struct frame *frame, struct bytecode_reader *reader) {}

#endif //TJVMSRC_INS_CONVERT_H
