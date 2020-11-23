//
// Created by tairy on 2020/11/17.
//

#include "stdlib.h"
#include "util/util.h"
#include "class_loader.h"

struct i_klass *load_no_array_class(struct class_loader *class_loader, char *class_name);

struct i_klass *define_class(struct class_loader *class_loader, struct class_file *class_file);

void resolve_super_class(struct i_klass *clazz);

void resolve_interfaces(struct i_klass *clazz);

void link(struct i_klass *clazz);

void verify(struct i_klass *clazz);

void prepare(struct i_klass *clazz);

struct class_loader *new_class_loader(struct class_path *class_path) {
    struct class_loader *class_loader = NEW(struct class_loader);
    class_loader->class_path = class_path;
    class_loader->class_map = create_hash_map(NULL, NULL);

    return class_loader;
}

struct i_klass *load_class(struct class_loader *class_loader, char *class_name) {
    if (default_exists_func(class_loader->class_map, class_name)) {
        return default_get_func(class_loader->class_map, class_name);
    }

    return load_no_array_class(class_loader, class_name);
}

struct i_klass *load_no_array_class(struct class_loader *class_loader, char *class_name) {
    struct class_source *source = class_loader->class_path->read_class(class_loader->class_path, class_name);

    if (source == NULL) {
        return NULL;
    }
    printf("class_name: %s, len: %d\n", source->name, source->len);
    struct class_reader *reader = build_class_reader(source);
    struct class_file *class_file = read_as_class_file(reader);
    printf("file_magic: %x\n", class_file->magic);
    struct i_klass *clazz = define_class(class_loader, class_file);
    link(clazz);
    default_put_func(class_loader->class_map, class_name, clazz);
    return clazz;
}

struct i_klass *define_class(struct class_loader *class_loader, struct class_file *class_file) {
    struct i_klass *clazz = new_klass(class_loader, class_file);
    printf("access_flags: %d, class_name: %s, super_class_name: %s\n",
           clazz->access_flags,
           clazz->name,
           clazz->super_class_name
    );
    resolve_super_class(clazz);
    resolve_interfaces(clazz);
}

void resolve_super_class(struct i_klass *clazz) {
    if (strcmp(clazz->super_class_name, "java/lang/Object") != 0) {
        clazz->super_class = load_class(clazz->class_loader, clazz->super_class_name);
    }
}

void resolve_interfaces(struct i_klass *clazz) {
    // todo
}

void link(struct i_klass *clazz) {
    verify(clazz);
    prepare(clazz);
}

void verify(struct i_klass *clazz) {
    // todo
}

void prepare(struct i_klass *clazz) {
    // todo
    // 给变量分配空间并给予初始值
}

