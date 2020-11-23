//
// Created by tairy on 2020/11/17.
//

#include "stdlib.h"
#include "util/util.h"
#include "class_loader.h"

struct i_klass *load_no_array_class(struct class_loader *class_loader, char *class_name);

struct class_loader *new_class_loader(struct class_path *class_path) {
    struct class_loader *class_loader = NEW(struct class_loader);
    class_loader->class_path = class_path;
    class_loader->class_map = NEW_HASH_MAP();
}

struct i_klass *load_class(struct class_loader *class_loader, char *class_name) {
    if (default_exists_func(class_loader->class_map, class_name)) {
        return default_get_func(class_loader->class_map, class_name);
    }

    return load_no_array_class(class_loader, class_name);
}

struct i_klass *load_no_array_class(struct class_loader *class_loader, char *class_name) {
    struct class_source *source = class_loader->class_path->read_class(class_loader->class_path, class_name);
    printf("class_name: %s, len: %d\n", source->name, source->len);
    struct class_reader *reader = build_class_reader(source);
    struct class_file *class_file = read_as_class_file(reader);
    printf("file_magic: %x\n", class_file->magic);
    struct i_klass *clazz = new_klass(class_file);
    printf("access_flags: %d, class_name: %s, super_class_name: %s\n",
           clazz->access_flags,
           clazz->name,
           clazz->super_class_name
    );
    default_put_func(class_loader->class_map, class_name, clazz);
    return clazz;
}

