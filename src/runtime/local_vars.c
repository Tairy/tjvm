//
// Created by tairy on 2020/11/17.
//

#include "local_vars.h"

struct local_vars *new_local_vars(u_int32_t max_locals) {
    if (max_locals > 0) {
        // todo need test.
        struct local_vars *local_vars = malloc(sizeof(struct local_vars));
        local_vars->size = max_locals;

        local_vars->vars = malloc(sizeof(union slot *) * max_locals);
        for (int i = 0; i < max_locals; i++) {
            local_vars->vars[i] = malloc(sizeof(union slot));
        }

        return local_vars;
    }

    return NULL;
}

void *get_this(struct local_vars *vars) {
    return get_ref(vars, 0);
}

void set_ref(struct local_vars *vars, u_int32_t index, void *ref) {
    vars->vars[index]->ref = ref;
}

void *get_ref(struct local_vars *vars, u_int32_t index) {
    return vars->vars[index]->ref;
}

void set_var(struct local_vars *vars, u_int32_t index, union slot *var) {
    vars->vars[index] = var;
}

union slot *get_var(struct local_vars *vars, u_int32_t index) {
    return vars->vars[index];
}

void set_int(struct local_vars *vars, u_int32_t index, int32_t val) {
    vars->vars[index]->num = val;
}

int32_t get_int(struct local_vars *vars, u_int32_t index) {
    return vars->vars[index]->num;
}

void set_long(struct local_vars *vars, u_int32_t index, int64_t val) {
    vars->vars[index]->num = (u_int32_t) (val >> 32);
    vars->vars[index + 1]->num = (u_int32_t) (val);
}

int64_t get_long(struct local_vars *vars, u_int32_t index) {
    union slot *slot = vars->vars[index];
    return (int64_t) vars->vars[index]->num << 32 | (int64_t) vars->vars[index + 1]->num;
}

void set_float(struct local_vars *vars, u_int32_t index, float val) {
    vars->vars[index]->num = val;  // todo maybe error here.
}

float get_float(struct local_vars *vars, u_int32_t index) {
    return (float) vars->vars[index]->num;
}

void set_double(struct local_vars *vars, u_int32_t index, double val) {

}

double get_double(struct local_vars *vars, u_int32_t index) {

}