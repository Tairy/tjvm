//
// Created by tairy on 2020/11/14.
//

#ifndef TJVMSRC_UTIL_H
#define TJVMSRC_UTIL_H

#include <stdio.h>

void print_byte_code(char *bytes, unsigned int len) {
    for (int i = 1; i < len + 1; i++) {
        printf("%02hhx\t", bytes[i - 1]);
        if (i % 40 == 0) {
            printf("\n");
        }
    }
}

#endif //TJVMSRC_UTIL_H
