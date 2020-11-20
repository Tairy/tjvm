//
// Created by tairy on 2020/11/20.
//
#include <stdio.h>
#include "class_path/class_path.h"
#include "class_file/class_reader.h"
#include "class_file/class_file.h"
#include "class_file/member_info.h"
#include "runtime/class.h"
#include "interpreter/bytecode_interpreter.h"

void start_tjvm();

struct method *get_main_method(struct class_file *class_file);

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
    struct method *main_method = get_main_method(class_file);
    struct bytecode_interpreter *b = build_bytecode_interpreter();
    struct thread *thread = create_thread();
    execute(b, thread, main_method);
}

struct method *get_main_method(struct class_file *class_file) {
    struct i_klass *clazz = new_klass(class_file);
    printf("access_flags: %d, class_name: %s, super_class_name: %s\n",
           clazz->access_flags,
           clazz->name,
           clazz->super_class_name
    );
    for (int i = 0, len = clazz->methods->size; i < len; i++) {
        struct method *m = clazz->methods->methods[i];
        if (strcmp(m->name, "main") == 0 && strcmp(m->descriptor, "([Ljava/lang/String;)V") == 0) {
            return m;
        }
    }

    return NULL;
}