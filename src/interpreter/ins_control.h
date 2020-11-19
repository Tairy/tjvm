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
    int32_t offset = (int32_t) next_int16(reader);
    frame->next_pc = frame->thread->pc + offset;
}

void insm_168(struct frame *frame, struct bytecode_reader *reader) {}

void insm_169(struct frame *frame, struct bytecode_reader *reader) {}

void insm_170(struct frame *frame, struct bytecode_reader *reader) {
    // TABLESWITCH
    skip_padding(reader);
    int32_t default_offset = next_int32(reader);
    int32_t low = next_int32(reader);
    int32_t high = next_int32(reader);
    int32_t offset_count = high - low + 1;
    int32_t *offsets = next_int32s(reader, offset_count);
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
    int32_t default_offset = next_int32(reader);
    int32_t offset_count = next_int32(reader);
    int32_t *offsets = next_int32s(reader, offset_count);
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

void insm_173(struct frame *frame, struct bytecode_reader *reader) {
    // LRETURN
    struct thread *thread = frame->thread;
    struct frame *current_frame = pop_frame(thread);
    struct frame *invoke_frame = top_frame(thread);
    push_long(invoke_frame->operand_stack, pop_long(current_frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_174(struct frame *frame, struct bytecode_reader *reader) {
    // FRETURN
    struct thread *thread = frame->thread;
    struct frame *current_frame = pop_frame(thread);
    struct frame *invoke_frame = top_frame(thread);
    push_float(invoke_frame->operand_stack, pop_float(current_frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_175(struct frame *frame, struct bytecode_reader *reader) {
    // DRETURN
    struct thread *thread = frame->thread;
    struct frame *current_frame = pop_frame(thread);
    struct frame *invoke_frame = top_frame(thread);
    push_double(invoke_frame->operand_stack, pop_double(current_frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_176(struct frame *frame, struct bytecode_reader *reader) {
    // ARETURN
    struct thread *thread = frame->thread;
    struct frame *current_frame = pop_frame(thread);
    struct frame *invoke_frame = top_frame(thread);
    push_ref(invoke_frame->operand_stack, pop_ref(current_frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_177(struct frame *frame, struct bytecode_reader *reader) {
    // OP_RETURN
    UPDATE_PC_AND_CONTINUE
}

#endif //TJVMSRC_INS_CONTROL_H
