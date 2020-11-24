//
// Created by tairy on 2020/11/17.
//

#include "slot.h"
#include "util/number.h"

void set_ref(union slot **vars, u_int32_t index, void *ref) {
    vars[index]->ref = ref;
}

void *get_ref(union slot **vars, u_int32_t index) {
    return vars[index]->ref;
}

void set_var(union slot **vars, u_int32_t index, union slot *var) {
    vars[index] = var;
}

union slot *get_var(union slot **vars, u_int32_t index) {
    return vars[index];
}

void set_int(union slot **vars, u_int32_t index, int32_t val) {
    vars[index]->num = val;
}

int32_t get_int(union slot **vars, u_int32_t index) {
    return vars[index]->num;
}

void set_long(union slot **vars, u_int32_t index, int64_t val) {
    vars[index]->num = (u_int32_t) (val >> 32);
    vars[index + 1]->num = (u_int32_t) (val);
}

int64_t get_long(union slot **vars, u_int32_t index) {
    return (int64_t) vars[index]->num << 32 | (int64_t) (vars[index + 1]->num);
}

void set_float(union slot **vars, u_int32_t index, float val) {
    vars[index]->num = float_to_raw_int_bits(val);
}

float get_float(union slot **vars, u_int32_t index) {
    return int_bits_to_float(vars[index]->num);
}

void set_double(union slot **vars, u_int32_t index, double val) {
    int64_t int_val = double_to_raw_int_bits(val);
    set_long(vars, index, int_val);
}

double get_double(union slot **vars, u_int32_t index) {
    int64_t int_val = get_long(vars, index);
    return int_bits_to_double(int_val);
}