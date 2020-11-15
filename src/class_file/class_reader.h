//
// Created by tairy on 2020/11/15.
//

#ifndef TJVMSRC_CLASS_READER_H
#define TJVMSRC_CLASS_READER_H

#include "stdlib.h"
#include "string.h"
#include "class_path/class_path.h"

struct class_reader {

    u_int32_t position;

    u_int32_t len;

    char *data;

};

static struct class_reader *build_class_reader(struct class_source *class_source) {
    struct class_reader *rs = (struct class_reader *) malloc(sizeof(struct class_reader));
    rs->position = 0;
    rs->len = class_source->len;
    rs->data = class_source->bytes;

    return rs;
}

static u_int8_t read_uint8(struct class_reader *r) {
    return r->data[r->position++];
}

static u_int16_t read_uint16(struct class_reader *r) {
    return (u_int16_t) r->data[r->position] << 8 | (u_int16_t) r->data[r->position++];
}

static u_int32_t read_uint32(struct class_reader *r) {
    u_int8_t x1 = r->data[r->position++];
    u_int8_t x2 = r->data[r->position++];
    u_int8_t x3 = r->data[r->position++];
    u_int8_t x4 = r->data[r->position++];

    return (u_int32_t) x1 << 24 | (u_int32_t) x2 << 16 | (u_int32_t) x3 << 8 | (u_int32_t) x4;
}

static u_int64_t read_uint64(struct class_reader *r) {
    u_int8_t x1 = r->data[r->position++];
    u_int8_t x2 = r->data[r->position++];
    u_int8_t x3 = r->data[r->position++];
    u_int8_t x4 = r->data[r->position++];

    u_int32_t h = (u_int32_t) x1 << 24 | (u_int32_t) x2 << 16 | (u_int32_t) x3 << 8 | (u_int32_t) x4;

    x1 = r->data[r->position++];
    x2 = r->data[r->position++];
    x3 = r->data[r->position++];
    x4 = r->data[r->position++];

    u_int32_t l = (u_int32_t) x1 << 24 | (u_int32_t) x2 << 16 | (u_int32_t) x3 << 8 | (u_int32_t) x4;

    return (u_int64_t) h << 32 | (u_int64_t) l;
}

static u_int16_t *read_uint16_s(struct class_reader *r, u_int16_t *size) {
    u_int16_t *rs = (u_int16_t *) malloc((*size = read_uint16(r)) * sizeof(u_int16_t));
    for (int i = 0; i < (*size); i++) {
        rs[i] = read_uint16(r);
    }

    return rs;
}

static char *read_bytes(struct class_reader *r, u_int32_t n) {
    u_int32_t len = n * sizeof(char) + 1;
    char *rs = (char *) malloc(len);
    memset(rs, 0, len);
    memcpy(rs, r->data + r->position, n);
    r->position += n;
    return rs;
}

#endif //TJVMSRC_CLASS_READER_H
