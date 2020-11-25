//
// Created by tairy on 2020/11/25.
//

#ifndef TJVMSRC_METHOD_DESCRIPTOR_H
#define TJVMSRC_METHOD_DESCRIPTOR_H

#include "stdlib.h"

struct method_descriptor {
    u_int16_t param_size;
    char **param_types;
    char *return_type;
};

static struct method_descriptor *new_method_descriptor() {
    struct method_descriptor *descriptor = malloc(sizeof(struct method_descriptor));
    descriptor->param_size = 0;
    return descriptor;
}

static void add_param_type(struct method_descriptor *descriptor, char *type) {
    char **new_param_types = malloc(sizeof(char *) * (descriptor->param_size + 1));
    int i;
    for (i = 0; i < descriptor->param_size; i++) {
        new_param_types[i] = descriptor->param_types[i];
    }
    new_param_types[i] = type;

    if (descriptor->param_size > 0) {
        free(descriptor->param_types);
    }
    descriptor->param_types = new_param_types;
    descriptor->param_types[descriptor->param_size] = type;
    descriptor->param_size++;
}

#endif //TJVMSRC_METHOD_DESCRIPTOR_H
