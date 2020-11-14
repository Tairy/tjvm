//
// Created by tairy on 2020/11/14.
//

#include <stdio.h>
#include "util/file.h"
#include "classpath/classpath.h"
#include "util/log.h"
#include "util/util.h"

int main() {
    printf("Welcome to tjvm, just enjoy it.\n");
    struct class_path *class_path = build_class_path("/home/tairy/Documents/Working/tjvm/tmp",
                                                     "/home/tairy/Documents/Working/tjvm/tmp");
    struct class_source *source = class_path->read_class(class_path, "Hello.class");
    print_byte_code(source->bytes, source->len);
    printf("\nclass_name: %s\n", source->name);
    return 0;
}