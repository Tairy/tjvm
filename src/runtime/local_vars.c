//
// Created by tairy on 2020/11/17.
//

#include "local_vars.h"
#include "slot.h"

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