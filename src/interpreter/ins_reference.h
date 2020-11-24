//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_INS_REFERENCE_H
#define TJVMSRC_INS_REFERENCE_H

#include "runtime/frame.h"
#include "runtime/class.h"
#include "bytecode_reader.h"
#include "bytecode_interpreter.h"
#include "runtime/class_ref.h"
#include "runtime/object.h"

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

void insm_187(struct frame *frame, struct bytecode_reader *reader) {
    // NEW
    u_int16_t class_index = read_uint16(reader);
    struct class_ref *class_ref = frame->method->clazz->runtime_constant_pool->infos[class_index]->data;
    resolve_class_ref(class_ref, frame->method->clazz->class_loader);

    // TODO 未验证类的可访问性
    struct object *ref = new_object(class_ref->clazz);
    push_ref(frame->operand_stack, ref);
}

void insm_188(struct frame *frame, struct bytecode_reader *reader) {}

void insm_189(struct frame *frame, struct bytecode_reader *reader) {}

void insm_190(struct frame *frame, struct bytecode_reader *reader) {}

void insm_191(struct frame *frame, struct bytecode_reader *reader) {}

void insm_192(struct frame *frame, struct bytecode_reader *reader) {}

void insm_193(struct frame *frame, struct bytecode_reader *reader) {}

void insm_194(struct frame *frame, struct bytecode_reader *reader) {}

void insm_195(struct frame *frame, struct bytecode_reader *reader) {}

#endif //TJVMSRC_INS_REFERENCE_H
