//
// Created by tairy on 2020/11/17.
//
#include <stdio.h>
#include "class_path/class_path.h"
#include "util/util.h"

int main() {
    struct class_path *class_path = build_class_path("/home/tairy/Documents/Working/tjvm/tmp",
                                                     "/home/tairy/Documents/Working/tjvm/tmp");
    struct class_source *source = class_path->read_class(class_path, "Hello.class");
    printf("class_name: %s, len: %d\n", source->name, source->len);
    print_byte_code(source->bytes, source->len);
    return 0;
}
