//
// Created by tairy on 2020/11/18.
//

#ifndef TJVMSRC_BYTECODE_READER_H
#define TJVMSRC_BYTECODE_READER_H

#include "stdlib.h"

struct bytecode_reader {

    u_int32_t pc;

    char *code;
};

static u_int8_t read_uint8(struct bytecode_reader *r) {
    return r->code[r->pc++];
}

static int8_t read_int8(struct bytecode_reader *r) {
    int8_t x = *((int8_t *) r->code);
    r->pc++;
    return x;
}

static u_int16_t read_uint16(struct bytecode_reader *r) {
    return (u_int16_t) r->code[r->pc++] | (u_int16_t) r->code[r->pc++];
}

static int16_t read_int16(struct bytecode_reader *r) {
    return (u_int16_t) r->code[r->pc++] | (u_int16_t) r->code[r->pc++];
}

static u_int32_t read_uint32(struct bytecode_reader *r) {
    int8_t x1 = r->code[r->pc++];
    int8_t x2 = r->code[r->pc++];
    int8_t x3 = r->code[r->pc++];
    int8_t x4 = r->code[r->pc++];

    return (u_int32_t) x1 << 24 | (u_int32_t) x2 << 16 | (u_int32_t) x3 << 8 | (u_int32_t) x4;
}

static int32_t read_int32(struct bytecode_reader *r) {
    int8_t x1 = r->code[r->pc++];
    int8_t x2 = r->code[r->pc++];
    int8_t x3 = r->code[r->pc++];
    int8_t x4 = r->code[r->pc++];

    return (int32_t) x1 << 24 | (int32_t) x2 << 16 | (int32_t) x3 << 8 | (int32_t) x4;
}


// tableswitch he lookupswitch 使用
static int32_t *read_int32s(struct bytecode_reader *r, u_int32_t size) {
    int32_t *rs = (int32_t *) malloc(size * sizeof(int32_t));
    for (int i = 0; i < size; i++) {
        rs[i] = read_int32(r);
    }

    return rs;
}

static void skip_padding(struct bytecode_reader *r) {
    while (r->pc % 4 != 0) {
        read_uint8(r);
    }
}

#endif //TJVMSRC_BYTECODE_READER_H
