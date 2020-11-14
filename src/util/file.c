//
// Created by tairy on 2020/11/14.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "file.h"

/**
 * 根据 path 读取文件数据
 * @param file_path path
 * @return tjvm 文件结构体实例
 */
struct tjvm_file *read_file(char *file_path) {
    struct tjvm_file *r = malloc(sizeof(struct tjvm_file));
    FILE *f = fopen(file_path, "r");
    char *buffer = 0;

    u_int32_t file_len = 0;

    if (f) {
        fseek(f, 0, SEEK_END);
        file_len = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(file_len);

        if (buffer) {
            fread(buffer, 1, file_len, f);
        }

        fclose(f);
    }

    r->data = buffer;
    r->len = file_len;
    char *s = strrchr(file_path, '/');

    u_int32_t name_len = strlen(s) - 1;
    r->name = malloc(name_len + 1);
    r->name[name_len] = '\0';
    memcpy(r->name, s + 1, name_len);
    return r;
}

static void _list_dir(struct tjvm_file_list *file_list, char *dir_path, char *suffix, int recursive);

/**
 * 遍历目录中指定后缀文件
 * @param dir 目录
 * @param suffix 文件后缀
 * @param recursive
 * @return 文件列表结构体
 */
struct tjvm_files *list_dir(char *dir, char *suffix, int recursive) {
    unsigned long dir_str_len = strlen(dir);
    char *c_dir = dir;
    if (dir[dir_str_len - 1] == '/') {
        c_dir = malloc(dir_str_len);
        memset(c_dir, 0, dir_str_len);
        memcpy(c_dir, dir, dir_str_len - 1);
    }

    struct tjvm_file_list *file_list = malloc(sizeof(struct tjvm_file_list));
    struct tjvm_file_node *head = malloc(sizeof(struct tjvm_file_node));

    file_list->head = head;
    file_list->current = head;
    file_list->len = 0;

    _list_dir(file_list, c_dir, suffix, recursive);

    u_int32_t len = file_list->len;
    struct tjvm_files *rs = malloc(sizeof(struct tjvm_files));
    struct tjvm_file **files = malloc(sizeof(sizeof(tjvm_file) * len));

    struct tjvm_file_node *prev;
    struct tjvm_file_node *node = file_list->head;

    for (int n = 0; n < len; n++) {
        prev = node;
        node = node->next;
        files[n] = node->file;
        free(prev);
    }

    free(node);
    free(file_list);

    rs->files = files;
    rs->len = len;

    return rs;
}

static void _list_dir(struct tjvm_file_list *file_list, char *dir, char *suffix, int recursive) {
    DIR *opened_dir;

    struct dirent *entry;
    if (!(opened_dir = opendir(dir))) {
        return;
    }

    while ((entry = readdir(opened_dir)) != NULL) {
        char *d_name = entry->d_name;
        if (entry->d_type == DT_DIR) {
            if (strcmp(d_name, ".") == 0 || strcmp(d_name, "..") == 0) {
                continue;
            }

            if (recursive) {
                char path[512];
                sprintf(path, "%s/%s", dir, d_name);
                _list_dir(file_list, path, suffix, recursive);
            }
        } else {
            char *s = strrchr(d_name, '.');
            if (s == NULL || strcmp(s, suffix) != 0) {
                continue;
            }

            struct tjvm_file *f = malloc(sizeof(struct tjvm_file));
            u_int32_t d_len = strlen(d_name) + 1;
            u_int32_t len = strlen(dir) + strlen(d_name) + 2;
            f->path = malloc(len);
            f->name = malloc(d_len);
            memset(f->path, 0, len);
            memset(f->name, 0, d_len);
            strcat(f->path, dir);
            strcat(f->path, "/");
            strcat(f->path, d_name);
            strcat(f->name, d_name);

            struct tjvm_file_node *node = malloc(sizeof(struct tjvm_file_node));
            node->file = f;
            file_list->current->next = node;
            file_list->len++;
            file_list->current = node;
        }
    }

    closedir(opened_dir);
}
