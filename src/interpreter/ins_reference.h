//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_REFERENCE_H
#define TJVMSRC_INS_REFERENCE_H

#include "runtime/frame.h"
#include "runtime/class.h"
#include "bytecode_reader.h"
#include "bytecode_interpreter.h"

void insm_178(struct frame *frame, struct bytecode_reader *reader) {
    // GETSTATIC 获取指定类的静态类，并将其压入栈顶
//    int16_t field_ref_index = next_int16(reader);
//    struct i_klass *clazz = frame->method->clazz;
//    struct member_ref *field_ref = (struct member_ref *) get_runtime_constant_pool_info(clazz->constant_pool,
//    field_ref_index)->data;
//    struct field *field = resol

}

void insm_179(struct frame *frame, struct bytecode_reader *reader) {}

void insm_180(struct frame *frame, struct bytecode_reader *reader) {}

void insm_181(struct frame *frame, struct bytecode_reader *reader) {}

void insm_182(struct frame *frame, struct bytecode_reader *reader) {}

void insm_183(struct frame *frame, struct bytecode_reader *reader) {}

void insm_184(struct frame *frame, struct bytecode_reader *reader) {}

void insm_185(struct frame *frame, struct bytecode_reader *reader) {}

void insm_186(struct frame *frame, struct bytecode_reader *reader) {}

void insm_187(struct frame *frame, struct bytecode_reader *reader) {}

void insm_188(struct frame *frame, struct bytecode_reader *reader) {}

void insm_189(struct frame *frame, struct bytecode_reader *reader) {}

void insm_190(struct frame *frame, struct bytecode_reader *reader) {}

void insm_191(struct frame *frame, struct bytecode_reader *reader) {}

void insm_192(struct frame *frame, struct bytecode_reader *reader) {}

void insm_193(struct frame *frame, struct bytecode_reader *reader) {}

void insm_194(struct frame *frame, struct bytecode_reader *reader) {}

void insm_195(struct frame *frame, struct bytecode_reader *reader) {}

#endif //TJVMSRC_INS_REFERENCE_H
