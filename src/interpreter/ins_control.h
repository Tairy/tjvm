//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_CONTROL_H
#define TJVMSRC_INS_CONTROL_H

#include "runtime/frame.h"
#include "bytecode_interpreter.h"
#include "bytecode_reader.h"

void insm_167(struct frame *frame, struct bytecode_reader *reader) {
    // GOTO
    int32_t offset = (int32_t) read_int16(reader);
    frame->next_pc = frame->thread->pc + offset;
}

void insm_168(struct frame *frame, struct bytecode_reader *reader) {}

void insm_169(struct frame *frame, struct bytecode_reader *reader) {}

void insm_170(struct frame *frame, struct bytecode_reader *reader) {
    // TABLESWITCH
    skip_padding(reader);
    int32_t default_offset = read_int32(reader);
    int32_t low = read_int32(reader);
    int32_t high = read_int32(reader);
    int32_t offset_count = high - low + 1;
    int32_t *offsets = read_int32s(reader, offset_count);
    int32_t index = pop_int(frame->operand_stack);
    int32_t offset;
    if (index >= low && index <= high) {
        offset = offsets[index - low];
    } else {
        offset = default_offset;
    }
    frame->next_pc = frame->thread->pc + offset;
}

void insm_171(struct frame *frame, struct bytecode_reader *reader) {
    // LOOKUPSWITCH
    skip_padding(reader);
    int32_t key = pop_int(frame->operand_stack);
    int32_t default_offset = read_int32(reader);
    int32_t offset_count = read_int32(reader);
    int32_t *offsets = read_int32s(reader, offset_count);
    for (int i = 0; i < offset_count; i = i + 2) {
        if (offsets[i] == key) {
            int32_t offset = offsets[i + 1];
            frame->next_pc = frame->thread->pc + offset;
            break;
        }
    }
}

void insm_172(struct frame *frame, struct bytecode_reader *reader) {
    // IRETURN
    struct thread *thread = frame->thread;
    struct frame *current_frame = pop_frame(thread);
    struct frame *invoke_frame = top_frame(thread);
    push_int(invoke_frame->operand_stack, pop_int(current_frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_173(struct frame *frame, struct bytecode_reader *reader) {}

void insm_174(struct frame *frame, struct bytecode_reader *reader) {}

void insm_175(struct frame *frame, struct bytecode_reader *reader) {}

void insm_176(struct frame *frame, struct bytecode_reader *reader) {}

void insm_177(struct frame *frame, struct bytecode_reader *reader) {}

#endif //TJVMSRC_INS_CONTROL_H
