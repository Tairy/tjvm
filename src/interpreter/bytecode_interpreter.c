//
// Created by tairy on 2020/11/18.
//

#include "bytecode_interpreter.h"
#include "ins_constant.h"

struct bytecode_interpreter *build_bytecode_interpreter() {
    struct bytecode_interpreter *interpreter = malloc(sizeof(struct bytecode_interpreter));
    REGISTER_INS_METHOD(interpreter, 0);
    return interpreter;
}

int execute(struct bytecode_interpreter *bytecode_interpreter, struct thread *thread, struct method *method) {
    struct frame *frame = new_frame(method->max_locals, method->max_stack);
    push_frame(thread, frame);
    struct bytecode_reader *reader = (struct bytecode_reader *) malloc(sizeof(struct bytecode_reader));
    struct frame *current;
    while ((current = top_frame(thread)) != NULL) {
        thread->pc = frame->next_pc;
        reader->code = current->method->code;
        reader->pc = frame->next_pc;
        u_int8_t op_code = read_uint8(reader);

        (*bytecode_interpreter->call[op_code])(current, reader);
    }

    return 0;
}

