//
// Created by tairy on 2020/11/14.
//

#ifndef TJVM_CLASSPATH_H
#define TJVM_CLASSPATH_H

#include "stdlib.h"

struct class_path {
    char *bootstrap_path;
    char *ext_path;
    char *user_path;

    struct class_source *(*read_class)(struct class_path *class_path, char *class_name);
} class_path;

struct class_source {
    u_int32_t len;
    char *bytes;
    char *name;
} class_source;

struct class_path *build_class_path(char *jre_path, char *cp_path);

/**
 * read_class 方法依次从启动类路径、扩展类路径和用户类路径中搜索 class 文件
 */
struct class_source *read_class(struct class_path *classPath, char *class_name);


#endif //TJVM_CLASSPATH_H
