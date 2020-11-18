//
// Created by tairy on 2020/11/14.
//

#include <stdio.h>
#include "class_path/class_path.h"
#include "class_file/class_reader.h"
#include "class_file/class_file.h"
#include "class_file/member_info.h"
#include "runtime/class.h"

void start_tjvm();

struct member_info *get_main_method(struct class_file *class_file);

int main() {
    start_tjvm();
    return 0;
}

void start_tjvm() {
    printf("Welcome to tjvm, just enjoy it.\n");
    struct class_path *class_path = build_class_path("/home/tairy/Documents/Working/tjvm/tmp",
                                                     "/home/tairy/Documents/Working/tjvm/tmp");
    struct class_source *source = class_path->read_class(class_path, "Hello.class");
    printf("class_name: %s, len: %d\n", source->name, source->len);
    struct class_reader *reader = build_class_reader(source);
    struct class_file *class_file = read_as_class_file(reader);
    printf("file_magic: %x\n", class_file->magic);
    struct member_info *main_method = get_main_method(class_file);
}

struct member_info *get_main_method(struct class_file *class_file) {
    struct i_klass *clazz = new_klass(class_file);
    printf("class_name: %s\n", clazz->name);
    for (int i = 0, len = class_file->methods->size; i < len; i++) {
        printf("method: %d\n", class_file->methods->infos[i]->name_index);
    }

    return NULL;
}