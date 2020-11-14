//
// Created by tairy on 2020/11/14.
//

#include <stdio.h>
#include "util/file.h"
#include "classpath/classpath.h"

int main() {
    printf("Welcome to tjvm, just enjoy it.\n");
//    read_class()
//    struct tjvm_file *tjvmFile = read_file("/home/tairy/Documents/Working/tjvm/src/util/file.c");
//    printf("file_len:%d", tjvmFile->len);
    struct class_path *class_path = build_class_path("/home/tairy/Documents/Working/tjvm/tmp",
                                                     "/home/tairy/Documents/Working/tjvm/tmp");
    struct class_source *source = class_path->read_class(class_path, "Hello.class");
    for (int i = 0; i < source->len; i++) {
        printf("%02hhx\t", source->bytes[i]);
        if (i > 0 && i % 40 == 0) {
            printf("\n");
        }
    }
    printf("\nclass_name: %s", source->name);
    return 0;
}