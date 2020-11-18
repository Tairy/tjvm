//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_STORE_H
#define TJVMSRC_INS_STORE_H

#include "runtime/frame.h"
#include "bytecode_reader.h"
#include "bytecode_interpreter.h"

void insm_54(struct frame *frame, struct bytecode_reader *reader) {
    // ISTORE 将 int 型数据存入指定变量表
    set_int(frame->local_vars, next_int8(reader), pop_int(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_55(struct frame *frame, struct bytecode_reader *reader) {
    // LSTORE
    set_long(frame->local_vars, next_int8(reader), pop_long(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_56(struct frame *frame, struct bytecode_reader *reader) {
    // FSTORE
    set_float(frame->local_vars, next_int8(reader), pop_float(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_57(struct frame *frame, struct bytecode_reader *reader) {
    // DSTORE
    set_double(frame->local_vars, next_int8(reader), pop_double(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_58(struct frame *frame, struct bytecode_reader *reader) {
    // ASTORE
    set_ref(frame->local_vars, next_int8(reader), pop_ref(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_59(struct frame *frame, struct bytecode_reader *reader) {
    // ISTORE_0
    set_int(frame->local_vars, 0, pop_int(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_60(struct frame *frame, struct bytecode_reader *reader) {
    // ISTORE_1
    set_int(frame->local_vars, 1, pop_int(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_61(struct frame *frame, struct bytecode_reader *reader) {
    // ISTORE_2
    set_int(frame->local_vars, 2, pop_int(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_62(struct frame *frame, struct bytecode_reader *reader) {
    // ISTORE_3
    set_int(frame->local_vars, 3, pop_int(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_63(struct frame *frame, struct bytecode_reader *reader) {
    // LSTORE_0
    set_long(frame->local_vars, 0, pop_long(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_64(struct frame *frame, struct bytecode_reader *reader) {
    // LSTORE_1
    set_long(frame->local_vars, 1, pop_long(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_65(struct frame *frame, struct bytecode_reader *reader) {
    // LSTORE_2
    set_long(frame->local_vars, 2, pop_long(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_66(struct frame *frame, struct bytecode_reader *reader) {
    // LSTORE_3
    set_long(frame->local_vars, 3, pop_long(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_67(struct frame *frame, struct bytecode_reader *reader) {
    // FSTORE_0
    set_float(frame->local_vars, 0, pop_float(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_68(struct frame *frame, struct bytecode_reader *reader) {
    // FSTORE_1
    set_float(frame->local_vars, 1, pop_float(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_69(struct frame *frame, struct bytecode_reader *reader) {
    // FSTORE_2
    set_float(frame->local_vars, 2, pop_float(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_70(struct frame *frame, struct bytecode_reader *reader) {
    // FSTORE_3
    set_float(frame->local_vars, 3, pop_float(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_71(struct frame *frame, struct bytecode_reader *reader) {
    // DSTORE_0
    set_double(frame->local_vars, 0, pop_double(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_72(struct frame *frame, struct bytecode_reader *reader) {
    // DSTORE_1
    set_double(frame->local_vars, 1, pop_double(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_73(struct frame *frame, struct bytecode_reader *reader) {
    // DSTORE_2
    set_double(frame->local_vars, 2, pop_double(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_74(struct frame *frame, struct bytecode_reader *reader) {
    // DSTORE_3
    set_double(frame->local_vars, 3, pop_double(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_75(struct frame *frame, struct bytecode_reader *reader) {
    // ASTORE_0
    set_ref(frame->local_vars, 0, pop_ref(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_76(struct frame *frame, struct bytecode_reader *reader) {
    // ASTORE_1
    set_ref(frame->local_vars, 1, pop_ref(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_77(struct frame *frame, struct bytecode_reader *reader) {
    // ASTORE_2
    set_ref(frame->local_vars, 2, pop_ref(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_78(struct frame *frame, struct bytecode_reader *reader) {
    // ASTORE_3
    set_ref(frame->local_vars, 3, pop_ref(frame->operand_stack));
    UPDATE_PC_AND_CONTINUE
}

void insm_79(struct frame *frame, struct bytecode_reader *reader) {}

void insm_80(struct frame *frame, struct bytecode_reader *reader) {}

void insm_81(struct frame *frame, struct bytecode_reader *reader) {}

void insm_82(struct frame *frame, struct bytecode_reader *reader) {}

void insm_83(struct frame *frame, struct bytecode_reader *reader) {}

void insm_84(struct frame *frame, struct bytecode_reader *reader) {}

void insm_85(struct frame *frame, struct bytecode_reader *reader) {}

void insm_86(struct frame *frame, struct bytecode_reader *reader) {}


#endif //TJVMSRC_INS_STORE_H
