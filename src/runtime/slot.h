//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_SLOT_H
#define TJVMSRC_SLOT_H

#include "stdlib.h"

union slot {
    u_int32_t num;
    void *ref;
};

union slots {
    u_int32_t num;
    union slot **vars;
};

#endif //TJVMSRC_SLOT_H
