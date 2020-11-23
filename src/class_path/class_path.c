//
// Created by tairy on 2020/11/14.
//

#include <string.h>
#include <zip.h>

#include "util/file.h"
#include "util/log.h"
#include "class_path.h"

static char *class_name_2_path(char *class_name);

struct class_source *read_bootstrap_class_path(struct class_path *class_path, char *class_name);

struct class_source *read_ext_class_path(struct class_path *class_path, char *class_name);

struct class_source *read_user_class_path(struct class_path *class_path, char *class_name);

static struct class_source *read_class_in_jar(char *jar_path, char *class_name);

static struct class_source *read_class_in_dir(char *dir, char *class_name);

static struct class_source *read_class_in_jar_dir(char *dir, char *class_name);

struct class_path *build_class_path(char *jre_path, char *cp_path) {
    struct class_path *r;
    r = malloc(sizeof(*r));

    if (r == NULL) {
        return NULL;
    }

    if (jre_path == NULL || strlen(jre_path) == 0) {
        jre_path = getenv("JAVA_HOME");
    }

    char *lib = "/jre/lib/";
    char *ext = "/jre/lib/ext/";
    unsigned int len_lib = strlen(jre_path) + strlen(lib) + 1;
    unsigned int len_ext = strlen(jre_path) + strlen(ext) + 1;
    char *lib_path = malloc(len_lib);
    char *ext_path = malloc(len_ext);

    memset(lib_path, 0, len_lib);
    memset(ext_path, 0, len_ext);
    strcat(lib_path, jre_path);
    strcat(lib_path, lib);
    strcat(ext_path, jre_path);
    strcat(ext_path, ext);

    r->read_class = read_class;
    r->bootstrap_path = lib_path;
    r->ext_path = ext_path;

    char *user_path = cp_path;
    u_int32_t len_user = strlen(user_path);
    if (user_path[len_user - 1] != '/') {
        user_path = malloc(len_user + 2);
        memset(user_path, 0, len_user + 2);
        memcpy(user_path, cp_path, len_user);
        strcat(user_path, "/");
    }

    r->user_path = user_path;

    return r;
}

struct class_source *read_class(struct class_path *class_path, char *class_name) {
    struct class_source *source;
    if ((source = read_bootstrap_class_path(class_path, class_name)) != NULL) {
        return source;
    } else if ((source = read_ext_class_path(class_path, class_name)) != NULL) {
        return source;
    } else {
        return read_user_class_path(class_path, class_name);
    }
}

static char *class_name_2_path(char *class_name) {
    unsigned int len = strlen(class_name);
    char *r = malloc(len + 1);

    memset(r, 0, len + 1);

    while (len--) {
        char *x = class_name + len;
        if (class_name[len] == '.' && strlen(x) != 5 && strcmp(x, ".class") != 0) {
            r[len] = '/';
        } else {
            r[len] = class_name[len];
        }
    }

    return r;
}

// TODO： 临时拼了一个函数，后续再完善
static char *get_class_file_name(char *class_name) {
    int32_t len = strlen(class_name);
    char *class_file_name_suffix = ".class";
    char *x;
    while (len--) {
        if (class_name[len] == '/') {
            x = class_name + len + 1;
            break;
        }
    }

    char *class_file_name = (char *) malloc(strlen(class_file_name_suffix) + strlen(x));
    sprintf(class_file_name, "%s%s", x, class_file_name_suffix);
    return class_file_name;
}

struct class_source *read_bootstrap_class_path(struct class_path *class_path, char *class_name) {
    return read_class_in_jar_dir(class_path->bootstrap_path, class_name);
}

struct class_source *read_ext_class_path(struct class_path *class_path, char *class_name) {
    return NULL;
}

struct class_source *read_user_class_path(struct class_path *class_path, char *class_name) {
    struct class_source *source = read_class_in_dir(class_path->user_path, class_name);
    if (source == NULL) {
        source = read_class_in_jar_dir(class_path->user_path, class_name);
    }

    return source;
}

static struct class_source *read_class_in_jar(char *jar_path, char *class_name) {
    int err;
    struct zip *z = zip_open(jar_path, 0, &err);
    if (err != 0 && err < 39) {
        log_error(__FILE__, __LINE__, "open jar file %s failed, error code: %d", jar_path, err);
        return NULL;
    }

    const char *name = class_name;
    struct zip_stat stat;
    zip_stat_init(&stat);
    zip_stat(z, name, 0, &stat);
    if (stat.size <= 0) {
        return NULL;
    }

    char *contents = malloc(stat.size);
    struct zip_file *f = zip_fopen(z, name, 0);

    zip_fread(f, contents, stat.size);
    zip_fclose(f);
    zip_close(z);

    struct class_source *source = (struct class_source *) malloc(sizeof(struct class_source));
    source->len = stat.size;
    source->bytes = contents;
    source->name = class_name;
    return source;
}

static struct class_source *read_class_in_dir(char *dir, char *class_name) {
    struct class_source *source = NULL;
    unsigned int path_len = strlen(dir);
    struct tjvm_files *files = list_dir(dir, ".class", 1);
    char *c_path = get_class_file_name(class_name);

    for (int i = 0, size = files->len; i < size; i++) {
        struct tjvm_file *f = files->files[i];
        char *path = f->path;
        char *x_path = path + path_len;
        if (strcmp(x_path, c_path) == 0) {
            struct tjvm_file *f = read_file(path);
            source = malloc(sizeof(struct class_source));
            source->bytes = f->data;
            source->len = f->len;
            source->name = malloc(strlen(class_name) + 1);
            memset(source->name, 0, strlen(class_name) + 1);
            memcpy(source->name, class_name, strlen(class_name));
            return source;
        }
    }

    return source;
}

static struct class_source *read_class_in_jar_dir(char *dir, char *class_name) {
    struct class_source *source = NULL;
    struct tjvm_files *files = list_dir(dir, ".jar", 1);
    for (int i = 0, size = files->len; i < size; i++) {
        struct tjvm_file *f = files->files[i];
        source = read_class_in_jar(f->path, class_name);

        if (source != NULL) {
            return source;
        }
    }

    return source;
}