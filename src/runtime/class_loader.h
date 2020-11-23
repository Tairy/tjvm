//
// Created by tairy on 2020/11/17.
//

#ifndef TJVMSRC_CLASS_LOADER_H
#define TJVMSRC_CLASS_LOADER_H

#include "class_path/class_path.h"
#include "util/hash_map.h"
#include "class.h"

struct class_loader {

    struct class_path *class_path;

    struct hash_map *class_map;
};

struct class_loader *new_class_loader(struct class_path *class_path);

struct i_klass *load_class(struct class_loader *class_loader, char *class_name);

#endif //TJVMSRC_CLASS_LOADER_H
