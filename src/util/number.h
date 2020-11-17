//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMTEST_NUMBER_H
#define TJVMTEST_NUMBER_H

static inline float int_bits_to_float(int i) {
    union {
        int i;
        float f;
    } u;
    u.i = i;
    return u.f;
}

static inline int float_to_raw_int_bits(float f) {
    union {
        int i;
        float f;
    } u;
    u.f = f;
    return u.i;
}

static inline double int_bits_to_double(int64_t i) {
    union {
        int64_t i;
        double d;
    } u;
    u.i = i;
    return u.d;
}

static inline double double_to_raw_int_bits(double d) {
    union {
        int64_t i;
        double d;
    } u;
    u.d = d;
    return u.i;
}

#endif //TJVMTEST_NUMBER_H
