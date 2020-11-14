//
// Created by tairy on 2020/11/14.
//

/**
 * 类文件加载，文件操作
 */
 
#ifndef TJVM_FILE_H
#define TJVM_FILE_H

#include <stdlib.h>

struct tjvm_file {
    char *path;
    char *name;
    u_int32_t len;
    char *data;
} tjvm_file;


struct tjvm_files {
    u_int32_t len;
    struct tjvm_file **files;
} tjvm_files;

// 链表存储文件数据
struct tjvm_file_node {
    struct tjvm_file *file;
    struct tjvm_file_node *next;
} tjvm_file_node;

struct tjvm_file_list {
    u_int32_t len;
    struct tjvm_file_node *head;
    struct tjvm_file_node *current;
} tjvm_file_list;

struct tjvm_file *read_file(char *file_path);

struct tjvm_files *list_dir(char *dir, char *suffix, int recursive);

#endif //TJVM_FILE_H
