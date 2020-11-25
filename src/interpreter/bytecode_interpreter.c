//
// Created by tairy on 2020/11/18.
//

#include "bytecode_interpreter.h"
#include "ins_constant.h"
#include "ins_load.h"
#include "ins_store.h"
#include "ins_compare.h"
#include "ins_control.h"
#include "ins_opcode.h"
#include "ins_stack.h"
#include "ins_math.h"
#include "ins_reference.h"
#include "ins_extend.h"
#include "ins_reserved.h"
#include "ins_convert.h"
#include "runtime/method.h"

struct bytecode_interpreter *build_bytecode_interpreter() {
    struct bytecode_interpreter *interpreter = malloc(sizeof(struct bytecode_interpreter));
    REGISTER_INS_METHOD(interpreter, OP_NOP);
    REGISTER_INS_METHOD(interpreter, OP_ACONST_NULL);
    REGISTER_INS_METHOD(interpreter, OP_ICONST_M1);
    REGISTER_INS_METHOD(interpreter, OP_ICONST_0);
    REGISTER_INS_METHOD(interpreter, OP_ICONST_1);
    REGISTER_INS_METHOD(interpreter, OP_ICONST_2);
    REGISTER_INS_METHOD(interpreter, OP_ICONST_3);
    REGISTER_INS_METHOD(interpreter, OP_ICONST_4);
    REGISTER_INS_METHOD(interpreter, OP_ICONST_5);
    REGISTER_INS_METHOD(interpreter, OP_LCONST_0);
    REGISTER_INS_METHOD(interpreter, OP_LCONST_1);
    REGISTER_INS_METHOD(interpreter, OP_FCONST_0);
    REGISTER_INS_METHOD(interpreter, OP_FCONST_1);
    REGISTER_INS_METHOD(interpreter, OP_FCONST_2);
    REGISTER_INS_METHOD(interpreter, OP_DCONST_0);
    REGISTER_INS_METHOD(interpreter, OP_DCONST_1);
    REGISTER_INS_METHOD(interpreter, OP_BIPUSH);
    REGISTER_INS_METHOD(interpreter, OP_SIPUSH);
    REGISTER_INS_METHOD(interpreter, OP_LDC);
    REGISTER_INS_METHOD(interpreter, OP_LDC_W);
    REGISTER_INS_METHOD(interpreter, OP_LDC2_W);
    REGISTER_INS_METHOD(interpreter, OP_ILOAD);
    REGISTER_INS_METHOD(interpreter, OP_LLOAD);
    REGISTER_INS_METHOD(interpreter, OP_FLOAD);
    REGISTER_INS_METHOD(interpreter, OP_DLOAD);
    REGISTER_INS_METHOD(interpreter, OP_ALOAD);
    REGISTER_INS_METHOD(interpreter, OP_ILOAD_0);
    REGISTER_INS_METHOD(interpreter, OP_ILOAD_1);
    REGISTER_INS_METHOD(interpreter, OP_ILOAD_2);
    REGISTER_INS_METHOD(interpreter, OP_ILOAD_3);
    REGISTER_INS_METHOD(interpreter, OP_LLOAD_0);
    REGISTER_INS_METHOD(interpreter, OP_LLOAD_1);
    REGISTER_INS_METHOD(interpreter, OP_LLOAD_2);
    REGISTER_INS_METHOD(interpreter, OP_LLOAD_3);
    REGISTER_INS_METHOD(interpreter, OP_FLOAD_0);
    REGISTER_INS_METHOD(interpreter, OP_FLOAD_1);
    REGISTER_INS_METHOD(interpreter, OP_FLOAD_2);
    REGISTER_INS_METHOD(interpreter, OP_FLOAD_3);
    REGISTER_INS_METHOD(interpreter, OP_DLOAD_0);
    REGISTER_INS_METHOD(interpreter, OP_DLOAD_1);
    REGISTER_INS_METHOD(interpreter, OP_DLOAD_2);
    REGISTER_INS_METHOD(interpreter, OP_DLOAD_3);
    REGISTER_INS_METHOD(interpreter, OP_ALOAD_0);
    REGISTER_INS_METHOD(interpreter, OP_ALOAD_1);
    REGISTER_INS_METHOD(interpreter, OP_ALOAD_2);
    REGISTER_INS_METHOD(interpreter, OP_ALOAD_3);
    REGISTER_INS_METHOD(interpreter, OP_IALOAD);
    REGISTER_INS_METHOD(interpreter, OP_LALOAD);
    REGISTER_INS_METHOD(interpreter, OP_FALOAD);
    REGISTER_INS_METHOD(interpreter, OP_DALOAD);
    REGISTER_INS_METHOD(interpreter, OP_AALOAD);
    REGISTER_INS_METHOD(interpreter, OP_BALOAD);
    REGISTER_INS_METHOD(interpreter, OP_CALOAD);
    REGISTER_INS_METHOD(interpreter, OP_SALOAD);
    REGISTER_INS_METHOD(interpreter, OP_ISTORE);
    REGISTER_INS_METHOD(interpreter, OP_LSTORE);
    REGISTER_INS_METHOD(interpreter, OP_FSTORE);
    REGISTER_INS_METHOD(interpreter, OP_DSTORE);
    REGISTER_INS_METHOD(interpreter, OP_ASTORE);
    REGISTER_INS_METHOD(interpreter, OP_ISTORE_0);
    REGISTER_INS_METHOD(interpreter, OP_ISTORE_1);
    REGISTER_INS_METHOD(interpreter, OP_ISTORE_2);
    REGISTER_INS_METHOD(interpreter, OP_ISTORE_3);
    REGISTER_INS_METHOD(interpreter, OP_LSTORE_0);
    REGISTER_INS_METHOD(interpreter, OP_LSTORE_1);
    REGISTER_INS_METHOD(interpreter, OP_LSTORE_2);
    REGISTER_INS_METHOD(interpreter, OP_LSTORE_3);
    REGISTER_INS_METHOD(interpreter, OP_FSTORE_0);
    REGISTER_INS_METHOD(interpreter, OP_FSTORE_1);
    REGISTER_INS_METHOD(interpreter, OP_FSTORE_2);
    REGISTER_INS_METHOD(interpreter, OP_FSTORE_3);
    REGISTER_INS_METHOD(interpreter, OP_DSTORE_0);
    REGISTER_INS_METHOD(interpreter, OP_DSTORE_1);
    REGISTER_INS_METHOD(interpreter, OP_DSTORE_2);
    REGISTER_INS_METHOD(interpreter, OP_DSTORE_3);
    REGISTER_INS_METHOD(interpreter, OP_ASTORE_0);
    REGISTER_INS_METHOD(interpreter, OP_ASTORE_1);
    REGISTER_INS_METHOD(interpreter, OP_ASTORE_2);
    REGISTER_INS_METHOD(interpreter, OP_ASTORE_3);
    REGISTER_INS_METHOD(interpreter, OP_IASTORE);
    REGISTER_INS_METHOD(interpreter, OP_LASTORE);
    REGISTER_INS_METHOD(interpreter, OP_FASTORE);
    REGISTER_INS_METHOD(interpreter, OP_DASTORE);
    REGISTER_INS_METHOD(interpreter, OP_AASTORE);
    REGISTER_INS_METHOD(interpreter, OP_BASTORE);
    REGISTER_INS_METHOD(interpreter, OP_CASTORE);
    REGISTER_INS_METHOD(interpreter, OP_SASTORE);
    REGISTER_INS_METHOD(interpreter, OP_POP);
    REGISTER_INS_METHOD(interpreter, OP_POP2);
    REGISTER_INS_METHOD(interpreter, OP_DUP);
    REGISTER_INS_METHOD(interpreter, OP_DUP_X1);
    REGISTER_INS_METHOD(interpreter, OP_DUP_X2);
    REGISTER_INS_METHOD(interpreter, OP_DUP2);
    REGISTER_INS_METHOD(interpreter, OP_DUP2_X1);
    REGISTER_INS_METHOD(interpreter, OP_DUP2_X2);
    REGISTER_INS_METHOD(interpreter, OP_SWAP);
    REGISTER_INS_METHOD(interpreter, OP_IADD);
    REGISTER_INS_METHOD(interpreter, OP_LADD);
    REGISTER_INS_METHOD(interpreter, OP_FADD);
    REGISTER_INS_METHOD(interpreter, OP_DADD);
    REGISTER_INS_METHOD(interpreter, OP_ISUB);
    REGISTER_INS_METHOD(interpreter, OP_LSUB);
    REGISTER_INS_METHOD(interpreter, OP_FSUB);
    REGISTER_INS_METHOD(interpreter, OP_DSUB);
    REGISTER_INS_METHOD(interpreter, OP_IMUL);
    REGISTER_INS_METHOD(interpreter, OP_LMUL);
    REGISTER_INS_METHOD(interpreter, OP_FMUL);
    REGISTER_INS_METHOD(interpreter, OP_DMUL);
    REGISTER_INS_METHOD(interpreter, OP_IDIV);
    REGISTER_INS_METHOD(interpreter, OP_LDIV);
    REGISTER_INS_METHOD(interpreter, OP_FDIV);
    REGISTER_INS_METHOD(interpreter, OP_DDIV);
    REGISTER_INS_METHOD(interpreter, OP_IREM);
    REGISTER_INS_METHOD(interpreter, OP_LREM);
    REGISTER_INS_METHOD(interpreter, OP_FREM);
    REGISTER_INS_METHOD(interpreter, OP_DREM);
    REGISTER_INS_METHOD(interpreter, OP_INEG);
    REGISTER_INS_METHOD(interpreter, OP_LNEG);
    REGISTER_INS_METHOD(interpreter, OP_FNEG);
    REGISTER_INS_METHOD(interpreter, OP_DNEG);
    REGISTER_INS_METHOD(interpreter, OP_ISHL);
    REGISTER_INS_METHOD(interpreter, OP_LSHL);
    REGISTER_INS_METHOD(interpreter, OP_ISHR);
    REGISTER_INS_METHOD(interpreter, OP_LSHR);
    REGISTER_INS_METHOD(interpreter, OP_IUSHR);
    REGISTER_INS_METHOD(interpreter, OP_LUSHR);
    REGISTER_INS_METHOD(interpreter, OP_IAND);
    REGISTER_INS_METHOD(interpreter, OP_LAND);
    REGISTER_INS_METHOD(interpreter, OP_IOR);
    REGISTER_INS_METHOD(interpreter, OP_LOR);
    REGISTER_INS_METHOD(interpreter, OP_IXOR);
    REGISTER_INS_METHOD(interpreter, OP_LXOR);
    REGISTER_INS_METHOD(interpreter, OP_IINC);
    REGISTER_INS_METHOD(interpreter, OP_I2L);
    REGISTER_INS_METHOD(interpreter, OP_I2F);
    REGISTER_INS_METHOD(interpreter, OP_I2D);
    REGISTER_INS_METHOD(interpreter, OP_L2I);
    REGISTER_INS_METHOD(interpreter, OP_L2F);
    REGISTER_INS_METHOD(interpreter, OP_L2D);
    REGISTER_INS_METHOD(interpreter, OP_F2I);
    REGISTER_INS_METHOD(interpreter, OP_F2L);
    REGISTER_INS_METHOD(interpreter, OP_F2D);
    REGISTER_INS_METHOD(interpreter, OP_D2I);
    REGISTER_INS_METHOD(interpreter, OP_D2L);
    REGISTER_INS_METHOD(interpreter, OP_D2F);
    REGISTER_INS_METHOD(interpreter, OP_I2B);
    REGISTER_INS_METHOD(interpreter, OP_I2C);
    REGISTER_INS_METHOD(interpreter, OP_I2S);
    REGISTER_INS_METHOD(interpreter, OP_LCMP);
    REGISTER_INS_METHOD(interpreter, OP_FCMPL);
    REGISTER_INS_METHOD(interpreter, OP_FCMPG);
    REGISTER_INS_METHOD(interpreter, OP_DCMPL);
    REGISTER_INS_METHOD(interpreter, OP_DCMPG);
    REGISTER_INS_METHOD(interpreter, OP_IFEQ);
    REGISTER_INS_METHOD(interpreter, OP_IFNE);
    REGISTER_INS_METHOD(interpreter, OP_IFLT);
    REGISTER_INS_METHOD(interpreter, OP_IFGE);
    REGISTER_INS_METHOD(interpreter, OP_IFGT);
    REGISTER_INS_METHOD(interpreter, OP_IFLE);
    REGISTER_INS_METHOD(interpreter, OP_IF_ICMPEQ);
    REGISTER_INS_METHOD(interpreter, OP_IF_ICMPNE);
    REGISTER_INS_METHOD(interpreter, OP_IF_ICMPLT);
    REGISTER_INS_METHOD(interpreter, OP_IF_ICMPGE);
    REGISTER_INS_METHOD(interpreter, OP_IF_ICMPGT);
    REGISTER_INS_METHOD(interpreter, OP_IF_ICMPLE);
    REGISTER_INS_METHOD(interpreter, OP_IF_ACMPEQ);
    REGISTER_INS_METHOD(interpreter, OP_IF_ACMPNE);
    REGISTER_INS_METHOD(interpreter, OP_GOTO);
    REGISTER_INS_METHOD(interpreter, OP_JSR);
    REGISTER_INS_METHOD(interpreter, OP_RET);
    REGISTER_INS_METHOD(interpreter, OP_TABLESWITCH);
    REGISTER_INS_METHOD(interpreter, OP_LOOKUPSWITCH);
    REGISTER_INS_METHOD(interpreter, OP_IRETURN);
    REGISTER_INS_METHOD(interpreter, OP_LRETURN);
    REGISTER_INS_METHOD(interpreter, OP_FRETURN);
    REGISTER_INS_METHOD(interpreter, OP_DRETURN);
    REGISTER_INS_METHOD(interpreter, OP_ARETURN);
    REGISTER_INS_METHOD(interpreter, OP_RETURN);
    REGISTER_INS_METHOD(interpreter, OP_GETSTATIC);
    REGISTER_INS_METHOD(interpreter, OP_PUTSTATIC);
    REGISTER_INS_METHOD(interpreter, OP_GETFIELD);
    REGISTER_INS_METHOD(interpreter, OP_PUTFIELD);
    REGISTER_INS_METHOD(interpreter, OP_INVOKEVIRTUAL);
    REGISTER_INS_METHOD(interpreter, OP_INVOKESPECIAL);
    REGISTER_INS_METHOD(interpreter, OP_INVOKESTATIC);
    REGISTER_INS_METHOD(interpreter, OP_INVOKEINTERFACE);
    REGISTER_INS_METHOD(interpreter, OP_INVOKEDYNAMIC);
    REGISTER_INS_METHOD(interpreter, OP_NEW);
    REGISTER_INS_METHOD(interpreter, OP_NEWARRAY);
    REGISTER_INS_METHOD(interpreter, OP_ANEWARRAY);
    REGISTER_INS_METHOD(interpreter, OP_ARRAYLENGTH);
    REGISTER_INS_METHOD(interpreter, OP_ATHROW);
    REGISTER_INS_METHOD(interpreter, OP_CHECKCAST);
    REGISTER_INS_METHOD(interpreter, OP_INSTANCEOF);
    REGISTER_INS_METHOD(interpreter, OP_MONITORENTER);
    REGISTER_INS_METHOD(interpreter, OP_MONITOREXIT);
//    REGISTER_INS_METHOD(interpreter, OP_WIDE);
//    REGISTER_INS_METHOD(interpreter, OP_MULTIANEWARRAY);
//    REGISTER_INS_METHOD(interpreter, OP_IFNULL);
//    REGISTER_INS_METHOD(interpreter, OP_IFNONNULL);
//    REGISTER_INS_METHOD(interpreter, OP_GOTO_W);
//    REGISTER_INS_METHOD(interpreter, OP_JSR_W);
//    REGISTER_INS_METHOD(interpreter, OP_BREAKPOINT);
//    REGISTER_INS_METHOD(interpreter, OP_IMPDEP1);
//    REGISTER_INS_METHOD(interpreter, OP_IMPDEP2);
    return interpreter;
}

int execute(struct bytecode_interpreter *bytecode_interpreter, struct thread *thread, struct method *method) {
    struct frame *frame = new_frame(thread, method);
    push_frame(thread, frame);

    // todo: reader need free.
    struct bytecode_reader *reader = (struct bytecode_reader *) malloc(sizeof(struct bytecode_reader));
    struct frame *current;
    while ((current = top_frame(thread)) != NULL) {
        thread->pc = current->next_pc;
        reader->code = current->method->code;
        reader->pc = current->next_pc;
        u_int8_t op_code = next_uint8(reader);
        printf("%x\t", op_code);
        (*bytecode_interpreter->call[op_code])(current, reader);
    }

    return 0;
}

