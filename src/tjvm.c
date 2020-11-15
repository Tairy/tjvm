//
// Created by tairy on 2020/11/14.
//

#include <stdio.h>
#include "class_path/class_path.h"
#include "class_file/class_reader.h"
#include "class_file/class_file.h"
#include "util/util.h"

int main() {
    printf("Welcome to tjvm, just enjoy it.\n");
    struct class_path *class_path = build_class_path("/home/tairy/Documents/Working/tjvm/tmp",
                                                     "/home/tairy/Documents/Working/tjvm/tmp");
    struct class_source *source = class_path->read_class(class_path, "Hello.class");

    struct class_reader *reader = build_class_reader(source);

    struct class_file *class_file = read_as_class_file(reader);

    printf("class_name: %s\n", source->name);
    printf("magic_file: %d\n", class_file->magic);
    return 0;
}