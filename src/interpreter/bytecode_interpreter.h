//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_BYTECODE_INTERPRETER_H
#define TJVMSRC_BYTECODE_INTERPRETER_H

#include "runtime/class.h"
#include "runtime/thread.h"
#include "bytecode_reader.h"

#define INS_METHOD(OP) insm_##OP
#define REGISTER_INS_METHOD(r, op) r->call[op] = INS_METHOD(op)

#define UPDATE_PC_AND_CONTINUE frame->next_pc = reader->pc;

struct bytecode_interpreter {
    void (*call[256])(struct frame *frame, struct bytecode_reader *reader);
};

struct bytecode_interpreter *build_bytecode_interpreter();

int execute(struct bytecode_interpreter *bytecode_interpreter, struct thread *thread, struct method *method);

#endif //TJVMSRC_BYTECODE_INTERPRETER_H
