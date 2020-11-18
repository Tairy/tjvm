//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_MATH_H
#define TJVMSRC_INS_MATH_H

#include "runtime/frame.h"
#include "bytecode_reader.h"
#include "bytecode_interpreter.h"

void insm_96(struct frame *frame, struct bytecode_reader *reader) {
    // IADD
    int32_t x1 = pop_int(frame->operand_stack);
    int32_t x2 = pop_int(frame->operand_stack);

    push_int(frame->operand_stack, (x1 + x2));
    UPDATE_PC_AND_CONTINUE
}

void insm_97(struct frame *frame, struct bytecode_reader *reader) {
    // LADD
    int64_t x1 = pop_long(frame->operand_stack);
    int64_t x2 = pop_long(frame->operand_stack);

    push_long(frame->operand_stack, (x1 + x2));
    UPDATE_PC_AND_CONTINUE
}

void insm_98(struct frame *frame, struct bytecode_reader *reader) {
    // FADD
    float x1 = pop_float(frame->operand_stack);
    float x2 = pop_float(frame->operand_stack);

    push_float(frame->operand_stack, (x1 + x2));
    UPDATE_PC_AND_CONTINUE
}

void insm_99(struct frame *frame, struct bytecode_reader *reader) {
    // DADD
    double x1 = pop_double(frame->operand_stack);
    double x2 = pop_double(frame->operand_stack);
    push_double(frame->operand_stack, (x1 + x2));
    UPDATE_PC_AND_CONTINUE
}

void insm_100(struct frame *frame, struct bytecode_reader *reader) {}

void insm_101(struct frame *frame, struct bytecode_reader *reader) {}

void insm_102(struct frame *frame, struct bytecode_reader *reader) {}

void insm_103(struct frame *frame, struct bytecode_reader *reader) {}

void insm_104(struct frame *frame, struct bytecode_reader *reader) {}

void insm_105(struct frame *frame, struct bytecode_reader *reader) {
    // LMUL
    int64_t x1 = pop_long(frame->operand_stack);
    int64_t x2 = pop_long(frame->operand_stack);

    push_long(frame->operand_stack, (x1 * x2));

    UPDATE_PC_AND_CONTINUE
}

void insm_106(struct frame *frame, struct bytecode_reader *reader) {}

void insm_107(struct frame *frame, struct bytecode_reader *reader) {}

void insm_108(struct frame *frame, struct bytecode_reader *reader) {}

void insm_109(struct frame *frame, struct bytecode_reader *reader) {}

void insm_110(struct frame *frame, struct bytecode_reader *reader) {}

void insm_111(struct frame *frame, struct bytecode_reader *reader) {}

void insm_112(struct frame *frame, struct bytecode_reader *reader) {}

void insm_113(struct frame *frame, struct bytecode_reader *reader) {}

void insm_114(struct frame *frame, struct bytecode_reader *reader) {}

void insm_115(struct frame *frame, struct bytecode_reader *reader) {}

void insm_116(struct frame *frame, struct bytecode_reader *reader) {}

void insm_117(struct frame *frame, struct bytecode_reader *reader) {}

void insm_118(struct frame *frame, struct bytecode_reader *reader) {}

void insm_119(struct frame *frame, struct bytecode_reader *reader) {}

void insm_120(struct frame *frame, struct bytecode_reader *reader) {}

void insm_121(struct frame *frame, struct bytecode_reader *reader) {}

void insm_122(struct frame *frame, struct bytecode_reader *reader) {}

void insm_123(struct frame *frame, struct bytecode_reader *reader) {}

void insm_124(struct frame *frame, struct bytecode_reader *reader) {}

void insm_125(struct frame *frame, struct bytecode_reader *reader) {
    // LUSHR
    u_int32_t offset = (u_int32_t) pop_int(frame->operand_stack);
    int64_t x = pop_long(frame->operand_stack);
    push_int(frame->operand_stack, ((u_int64_t) x) >> offset);
    UPDATE_PC_AND_CONTINUE
}

void insm_126(struct frame *frame, struct bytecode_reader *reader) {
    // IAND
    int32_t x1 = pop_int(frame->operand_stack);
    int32_t x2 = pop_int(frame->operand_stack);
    push_int(frame->operand_stack, (x1 & x2));
    UPDATE_PC_AND_CONTINUE
}

void insm_127(struct frame *frame, struct bytecode_reader *reader) {}

void insm_128(struct frame *frame, struct bytecode_reader *reader) {}

void insm_129(struct frame *frame, struct bytecode_reader *reader) {}

void insm_130(struct frame *frame, struct bytecode_reader *reader) {}

void insm_131(struct frame *frame, struct bytecode_reader *reader) {}

void insm_132(struct frame *frame, struct bytecode_reader *reader) {}

#endif //TJVMSRC_INS_MATH_H
