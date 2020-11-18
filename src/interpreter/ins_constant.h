//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_CONSTANT_H
#define TJVMSRC_INS_CONSTANT_H

#include "runtime/frame.h"
#include "bytecode_reader.h"
#include "bytecode_interpreter.h"

// 常量操作符
// NOP          0               0x00 什么都不做
// ACONST_NULL  1               0x01 将 null 推送到栈顶
// ICONST_M1    2               0x02 将 int 型 -1 推送至栈顶
// ICONST_0     3               0x03 将 int 型 0 推送至栈顶
// ICONST_1     4               0x04 将 int 型 1 推送至栈顶
// ICONST_2     5               0x05 将 int 型 2 推送至栈顶
// ICONST_3     6               0x06 将 int 型 3 推送至栈顶
// ICONST_4     7               0x07 将 int 型 4 推送至栈顶
// ICONST_5     8               0x08 将 int 型 5 推送至栈顶
// LCONST_0     9               0x09 将 long 型 0 推送到栈顶
// LCONST_1     10              0x0a 将 long 型 1 推送到栈顶
// FCONST_0     11              0x0b 将 float 型 0 推送到栈顶
// FCONST_1     12              0x0c 将 float 型 1 推送到栈顶
// FCONST_2     13              0x0d 将 float 型 2 推送到栈顶
// DCONST_0     14              0x0e 将 double 型 0 推送到栈顶
// DCONST_1     15              0x0f 将 double 型 1 推送到栈顶
// BIPUSH       16              0x10 将单字节常量值（-128~127）推送到栈顶
// SIPUSH       17              0x11 将一个短型常量值（-32768~32767）推送至栈顶
// LDC          18              0x12 将 int, float 或 String 型常量从常量池中推送至栈顶
// LDC_W        19              0x13 将 int, float 或 String 型常量从常量池中推送之栈顶（宽索引）
// LDC2_W       20              0x14 将 long 或 double 型常量值从常量池中推送至栈顶（宽索引）


void insm_0(struct frame *frame, struct bytecode_reader *reader) {
    // NOP
    UPDATE_PC_AND_CONTINUE
}

void insm_1(struct frame *frame, struct bytecode_reader *reader) {
    // ACONST_NULL
    push_ref(frame->operand_stack, NULL);
    UPDATE_PC_AND_CONTINUE
}

void insm_2(struct frame *frame, struct bytecode_reader *reader) {
    // ICONST_M1
    push_int(frame->operand_stack, -1);
    UPDATE_PC_AND_CONTINUE
}

void insm_3(struct frame *frame, struct bytecode_reader *reader) {
    // ICONST_0
    push_int(frame->operand_stack, 0);
    UPDATE_PC_AND_CONTINUE
}

void insm_4(struct frame *frame, struct bytecode_reader *reader) {
    // ICONST_1
    push_int(frame->operand_stack, 1);
    UPDATE_PC_AND_CONTINUE
}

void insm_5(struct frame *frame, struct bytecode_reader *reader) {
    // ICONST_2
    push_int(frame->operand_stack, 2);
    UPDATE_PC_AND_CONTINUE
}

void insm_6(struct frame *frame, struct bytecode_reader *reader) {
    // ICONST_3
    push_int(frame->operand_stack, 3);
    UPDATE_PC_AND_CONTINUE
}

void insm_7(struct frame *frame, struct bytecode_reader *reader) {
    // ICONST_4
    push_int(frame->operand_stack, 4);
    UPDATE_PC_AND_CONTINUE
}

void insm_8(struct frame *frame, struct bytecode_reader *reader) {
    // ICONST_5
    push_int(frame->operand_stack, 5);
    UPDATE_PC_AND_CONTINUE
}

void insm_9(struct frame *frame, struct bytecode_reader *reader) {
    // LCONST_0
    push_long(frame->operand_stack, 0);
    UPDATE_PC_AND_CONTINUE
}

void insm_10(struct frame *frame, struct bytecode_reader *reader) {
    // LCONST_1
    push_long(frame->operand_stack, 1);
    UPDATE_PC_AND_CONTINUE
}

void insm_11(struct frame *frame, struct bytecode_reader *reader) {
    // FCONST_0
    push_float(frame->operand_stack, 0);
    UPDATE_PC_AND_CONTINUE
}

void insm_12(struct frame *frame, struct bytecode_reader *reader) {
    // FCONST_1
    push_float(frame->operand_stack, 1);
    UPDATE_PC_AND_CONTINUE
}

void insm_13(struct frame *frame, struct bytecode_reader *reader) {
    // FCONST_2
    push_float(frame->operand_stack, 2);
    UPDATE_PC_AND_CONTINUE
}

void insm_14(struct frame *frame, struct bytecode_reader *reader) {
    // DCONST_0
    push_double(frame->operand_stack, 0);
    UPDATE_PC_AND_CONTINUE
}

void insm_15(struct frame *frame, struct bytecode_reader *reader) {
    // DCONST_1
    push_double(frame->operand_stack, 1);
    UPDATE_PC_AND_CONTINUE
}

void insm_16(struct frame *frame, struct bytecode_reader *reader) {
    // BIPUSH
    int32_t x = (int32_t) read_int8(reader);
    push_int(frame->operand_stack, x);
    UPDATE_PC_AND_CONTINUE
}

void insm_17(struct frame *frame, struct bytecode_reader *reader) {
    // SIPUSH
    int32_t x = read_int16(reader);
    push_int(frame->operand_stack, x);
    UPDATE_PC_AND_CONTINUE
}

void insm_18(struct frame *frame, struct bytecode_reader *reader) {}

void insm_19(struct frame *frame, struct bytecode_reader *reader) {}

void insm_20(struct frame *frame, struct bytecode_reader *reader) {}


#endif //TJVMSRC_INS_CONSTANT_H
