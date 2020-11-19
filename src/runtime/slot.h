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
#endif //TJVMSRC_SLOT_H
