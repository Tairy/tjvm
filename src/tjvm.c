//
// Created by tairy on 2020/11/14.
//

#include "stdio.h"
#include "class_path/class_path.h"
#include "class_file/class_reader.h"
#include "class_file/class_file.h"
#include "class_file/member_info.h"
#include "runtime/class.h"
#include "runtime/method.h"
#include "runtime/field.h"
#include "interpreter/bytecode_interpreter.h"
#include "runtime/class_loader.h"
#include "util/util.h"

void start_tjvm();

struct method *get_main_method(struct i_klass *clazz);

int main() {
    start_tjvm();
    return 0;
}

void start_tjvm() {
    printf("Welcome to tjvm, just enjoy it.\n");
    struct class_path *cp = build_class_path("/home/tairy/Documents/Working/tjvm/tmp",
                                             "/home/tairy/Documents/Working/tjvm/tmp");
    struct class_loader *class_loader = new_class_loader(cp);
    struct i_klass *clazz = load_class(class_loader, "com/sqkb/Hello");

    if (clazz == NULL) {
        return;
    }

//    struct method *main_method = get_main_method(clazz);
//    struct bytecode_interpreter *b = build_bytecode_interpreter();
//    struct thread *thread = create_thread();
//    execute(b, thread, main_method);
}

struct method *get_main_method(struct i_klass *clazz) {
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