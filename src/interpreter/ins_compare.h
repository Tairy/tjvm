//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_COMPARE_H
#define TJVMSRC_INS_COMPARE_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "runtime/runtime_constant_pool.h"
#include "bytecode_reader.h"
#include "bytecode_interpreter.h"

void insm_148(struct frame *frame, struct bytecode_reader *reader) {
    // LCMP
    int64_t v2 = pop_long(frame->operand_stack);
    int64_t v1 = pop_long(frame->operand_stack);
    push_int(frame->operand_stack, v1 > v2 ? 1 : (v1 == v2 ? 0 : -1));
    UPDATE_PC_AND_CONTINUE
}

void insm_149(struct frame *frame, struct bytecode_reader *reader) {
    // FCMPL
    float v2 = pop_float(frame->operand_stack);
    float v1 = pop_float(frame->operand_stack);

    push_int(frame->operand_stack, v1 > v2 ? 1 : (v1 == v2 ? 0 : -1));
    UPDATE_PC_AND_CONTINUE
}

void insm_150(struct frame *frame, struct bytecode_reader *reader) {
}

void insm_151(struct frame *frame, struct bytecode_reader *reader) {
    // DCMPL
    double v2 = pop_double(frame->operand_stack);
    double v1 = pop_double(frame->operand_stack);

    push_int(frame->operand_stack, v1 > v2 ? 1 : (v1 == v2 ? 0 : -1));
    UPDATE_PC_AND_CONTINUE
}

void insm_152(struct frame *frame, struct bytecode_reader *reader) {
    // DCMPG
    double v2 = pop_double(frame->operand_stack);
    double v1 = pop_double(frame->operand_stack);

    push_int(frame->operand_stack, v1 < v2 ? -1 : (v1 == v2 ? 0 : 1));
    UPDATE_PC_AND_CONTINUE
}

void insm_153(struct frame *frame, struct bytecode_reader *reader) {}

void insm_154(struct frame *frame, struct bytecode_reader *reader) {}

void insm_155(struct frame *frame, struct bytecode_reader *reader) {}

void insm_156(struct frame *frame, struct bytecode_reader *reader) {}

void insm_157(struct frame *frame, struct bytecode_reader *reader) {}

void insm_158(struct frame *frame, struct bytecode_reader *reader) {
    // IFLE
    int32_t v2 = pop_int(frame->operand_stack);
    int32_t v1 = pop_int(frame->operand_stack);
    int32_t offset = (int32_t) next_int16(reader);

    if (v1 == v2) {
        frame->next_pc = frame->thread->pc + offset;
    }
}

void insm_159(struct frame *frame, struct bytecode_reader *reader) {
    // IF_ICMPEQ
    int32_t v2 = pop_int(frame->operand_stack);
    int32_t v1 = pop_int(frame->operand_stack);
    int32_t offset = (int32_t) next_int16(reader);
    if (v1 == v2) {
        frame->next_pc = frame->thread->pc + offset;
    }
}

void insm_160(struct frame *frame, struct bytecode_reader *reader) {
    // IF_ICMPNE
    int32_t v1 = pop_int(frame->operand_stack);
    int32_t v2 = pop_int(frame->operand_stack);
    int32_t offset = (int32_t) next_int16(reader);

    if (v1 != v2) {
        frame->next_pc = frame->thread->pc + offset;
    }
}

void insm_161(struct frame *frame, struct bytecode_reader *reader) {
    // IF_ICMPLT
    int32_t v1 = pop_int(frame->operand_stack);
    int32_t v2 = pop_int(frame->operand_stack);
    int32_t offset = (int32_t) next_int16(reader);

    if (v1 < v2) {
        frame->next_pc = frame->thread->pc + offset;
    }
}

void insm_162(struct frame *frame, struct bytecode_reader *reader) {
    // IF_ICMPGE
    int32_t v1 = pop_int(frame->operand_stack);
    int32_t v2 = pop_int(frame->operand_stack);
    int32_t offset = (int32_t) next_int16(reader);

    if (v1 >= v2) {
        frame->next_pc = frame->thread->pc + offset;
    }
}

void insm_163(struct frame *frame, struct bytecode_reader *reader) {
    // IF_ICMPGT
    int32_t v1 = pop_int(frame->operand_stack);
    int32_t v2 = pop_int(frame->operand_stack);
    int32_t offset = (int32_t) next_int16(reader);

    if (v1 > v2) {
        frame->next_pc = frame->thread->pc + offset;
    }
}

void insm_164(struct frame *frame, struct bytecode_reader *reader) {
    // IF_ICMPLE
    int32_t v1 = pop_int(frame->operand_stack);
    int32_t v2 = pop_int(frame->operand_stack);
    int32_t offset = (int32_t) next_int16(reader);

    if (v1 <= v2) {
        frame->next_pc = frame->thread->pc + offset;
    }
}

void insm_165(struct frame *frame, struct bytecode_reader *reader) {}

void insm_166(struct frame *frame, struct bytecode_reader *reader) {
    // IF_ACMPNE
    void *r2 = pop_ref(frame->operand_stack);
    void *r1 = pop_ref(frame->operand_stack);
    int32_t offset = (int32_t) next_int16(reader);

    if (r1 != r2) {
        frame->next_pc = frame->thread->pc + offset;
    }
}

#endif //TJVMSRC_INS_COMPARE_H
