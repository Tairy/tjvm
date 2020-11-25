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
#include "runtime/method_ref.h"
#include "runtime/object.h"
#include "util/log.h"

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

void insm_183(struct frame *frame, struct bytecode_reader *reader) {
    // OP_INVOKESPECIAL 调用超类构造方法，实例初始化方法，私有方法
    u_int16_t method_ref_index = read_uint16(reader);
    struct i_klass *current_clazz = frame->method->clazz;
    struct method_ref *method_ref = current_clazz->runtime_constant_pool->infos[method_ref_index]->data;
    resolve_method_ref(method_ref, current_clazz);

    if (is_method_static(method_ref->method)) {
        log_error(__FILE__, __LINE__, "java.lang.IncompatibleClassChangeError.");
        return;
    }

    struct frame *n_frame = new_frame(frame->thread, method_ref->method);
    push_frame(frame->thread, n_frame);

    if (method_ref->method->arg_count > 0) {
        for (int i = (int) (method_ref->method->arg_count - 1); i >= 0; i--) {
            union slot *slot = pop_var(frame->operand_stack);
            set_var(n_frame->local_vars->vars, i, slot);
        }
    }
}

void insm_184(struct frame *frame, struct bytecode_reader *reader) {}

void insm_185(struct frame *frame, struct bytecode_reader *reader) {}

void insm_186(struct frame *frame, struct bytecode_reader *reader) {}

void insm_187(struct frame *frame, struct bytecode_reader *reader) {
    // NEW
    u_int16_t class_index = read_uint16(reader);
    struct class_ref *class_ref = frame->method->clazz->runtime_constant_pool->infos[class_index]->data;
    resolve_class_ref(class_ref, frame->method->clazz);
    // TODO 判断类是否被初始化

    // TODO 需要验证类的是否可被派生, 排除 abstract 和 interface.
    if (is_class_abstract(class_ref->clazz)) {
        log_error(__FILE__, __LINE__, "java.lang.InstantiationError.");
        return;
    }
    struct object *ref = new_object(class_ref->clazz);
    push_ref(frame->operand_stack, ref);
    UPDATE_PC_AND_CONTINUE
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
