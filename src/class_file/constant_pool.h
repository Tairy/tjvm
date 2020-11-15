//
// Created by tairy on 2020/11/15.
//

#ifndef TJVMSRC_CONSTANT_POOL_H
#define TJVMSRC_CONSTANT_POOL_H

#include <stdlib.h>

#define CONSTANT_Utf8_info                  1
#define CONSTANT_Integer_info               3
#define CONSTANT_Float_info                 4
#define CONSTANT_Long_info                  5
#define CONSTANT_Double_info                6
#define CONSTANT_Class_info                 7
#define CONSTANT_String_info                8
#define CONSTANT_Field_ref_info             9
#define CONSTANT_Method_ref_info            10
#define CONSTANT_Interface_Method_ref_info  11
#define CONSTANT_Name_And_Type_info         12
#define CONSTANT_Method_Handle_info         15
#define CONSTANT_Method_Type_info           16
#define CONSTANT_Invoke_Dynamic_info        18


struct cp_info {
    u_int8_t tag;
    void *v1;
    void *v2;
};

struct cp {
    u_int32_t len;
    struct cp_info **infos;
};

static char *get_utf8(struct cp *cp, u_int16_t index) {
    struct cp_info *ci = cp->infos[index];
    return (char *) ci->v1;
}

#endif //TJVMSRC_CONSTANT_POOL_H
