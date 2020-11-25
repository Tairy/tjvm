//
// Created by tairy on 2020/11/25.
//

#ifndef TJVMSRC_METHOD_DESCRIPTOR_PARSER_H
#define TJVMSRC_METHOD_DESCRIPTOR_PARSER_H

#include "method_descriptor.h"

struct method_descriptor_parser {
    char *raw;
    int offset;
    struct method_descriptor *parsed;
};

struct method_descriptor *parse_method_descriptor(char *descriptor);

#endif //TJVMSRC_METHOD_DESCRIPTOR_PARSER_H
