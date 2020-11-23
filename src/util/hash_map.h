//
// Created by tairy on 2020/11/20.
//

#ifndef TJVMTEST_HASH_MAP_H
#define TJVMTEST_HASH_MAP_H

#include "stdlib.h"
#include "string.h"
#include "util.h"

// 哈希函数类型

typedef int32_t (*hash_func)(struct hash_map *hash_map, void *key);

typedef int8_t (*equal_func)(void *key1, void *key2);

typedef void (*put_func)(struct hash_map *hash_map, void *key, void *value);

typedef void *(*get_func)(struct hash_map *hash_map, void *key);

typedef int8_t(*remove_func)(struct hash_map *hash_map, void *key);

typedef void (*clear_func)(struct hash_map *hash_map);

typedef int8_t (*exists_func)(struct hash_map *hash_map, void *key);

struct entry {
    void *key;
    void *value;
    struct entry *next;
};

#define NEW_ENTRY() NEW(struct entry)
#define NEW_ENTRY_LIST(length) (struct entry*)malloc(length * sizeof(struct entry))

struct hash_map {
    u_int32_t size;         // 当前大小
    u_int32_t list_size;    // 有效空间大小
    hash_func hash_func;    // 哈希函数
    equal_func equal_func;       // 判等函数
    struct entry *list;     // 数据区
    put_func put_func;           // put 函数
    get_func get_func;
    remove_func remove_func;     // remove 函数
    clear_func clear_func;
    exists_func exists_func;
};

#define NEW_HASH_MAP() NEW(struct hash_map)

struct hash_map_iterator {
    struct entry *entry;
    u_int32_t count;
    u_int32_t hash_code;
    struct hash_map *hash_map;
};

#define NEW_HASH_MAP_ITERATOR() NEW(struct hash_map_iterator)

static int32_t default_hash_func(struct hash_map *hash_map, void *key) {
    char *k = (char *) key;
    u_int64_t h = 0;

    while (*k) {
        h = (h << 4) + *k++;
        u_int64_t g = h & 0xF0000000L;
        if (g) {
            h ^= g >> 24;
        }
        h &= ~g;
    }

    return h % hash_map->list_size;
}

static int8_t default_equal_func(void *key1, void *key2) {
    return strcmp((char *) key1, (char *) key2) == 0 ? 1 : 0;
}

static void reset_hash_map(struct hash_map *hash_map, int list_size);

static void default_put_func(struct hash_map *hash_map, void *key, void *value) {

    if (hash_map->size >= hash_map->list_size) {
        reset_hash_map(hash_map, hash_map->list_size * 2);
    }

    int32_t index = hash_map->hash_func(hash_map, key);
    if (hash_map->list[index].key == NULL) {
        hash_map->size++;
        hash_map->list[index].key = key;
        hash_map->list[index].value = value;
    } else {
        struct entry *current = &hash_map->list[index];
        while (current != NULL) {
            if (hash_map->equal_func(key, current->key) == 1) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        struct entry *entry = NEW_ENTRY();
        entry->key = key;
        entry->value = value;
        entry->next = hash_map->list[index].next;
        hash_map->list[index].next = entry;
        hash_map->size++;
    }
}

static void *default_get_func(struct hash_map *hash_map, void *key) {
    if (hash_map->exists_func(hash_map, key)) {
        u_int32_t index = hash_map->hash_func(hash_map, key);
        struct entry *entry = &hash_map->list[index];
        while (entry != NULL) {
            if (hash_map->equal_func(entry->key, key) == 1) {
                return entry->value;
            }

            entry = entry->next;
        }
    }
}

static void *default_remove_func(struct hash_map *hash_map, void *key) {
    u_int32_t index = hash_map->hash_func(hash_map, key);
    struct entry *entry = &hash_map->list[index];
    if (entry->key == NULL) {
        return NULL;
    }

    void *entry_key = entry->key;
    u_int8_t result = 0;
    if (hash_map->equal_func(entry->key, key) == 1) {
        hash_map->size--;
        if (entry->next != NULL) {
            struct entry *temp = entry->next;
            entry->key = temp->key;
            entry->value = temp->value;
            entry->next = temp->next;
            free(temp);
        } else {
            entry->key = NULL;
            entry->value = NULL;
        }
        result = 1;
    } else {
        struct entry *p = entry;
        entry = entry->next;
        while (entry != NULL) {
            if (hash_map->equal_func(entry->key, key) == 1) {
                hash_map->size--;
                p->next = entry->next;
                free(entry);
                result = 1;
                break;
            }
            p = entry;
            entry = entry->next;
        }
    }

    if (result && hash_map->size < hash_map->list_size / 2) {
        reset_hash_map(hash_map, hash_map->list_size / 2);
    }
    return entry_key;
}

static int8_t default_exists_func(struct hash_map *hash_map, void *key) {
    u_int32_t index = hash_map->hash_func(hash_map, key);
    struct entry *entry = &hash_map->list[index];
    if (entry->key == NULL) {
        return 0;
    } else {
        while (entry != NULL) {
            if (hash_map->equal_func(entry->key, key) == 1) {
                return 1;
            }

            entry = entry->next;
        }
        return 0;
    }
}

static void default_clear(struct hash_map *hash_map) {
    for (int i = 0; i < hash_map->list_size; i++) {
        struct entry *entry = hash_map->list[i].next;
        while (entry != NULL) {
            struct entry *next = entry->next;
            free(entry);
            entry = next;
        }

        hash_map->list[i].next = NULL;
    }

    free(hash_map->list);
    hash_map->list = NULL;
    hash_map->size = -1;
    hash_map->list_size = 0;
}

static struct hash_map *create_hash_map(hash_func *hash_func, equal_func equal_func) {
    struct hash_map *hash_map = NEW_HASH_MAP();
    if (hash_map == NULL) {
        return NULL;
    }

    hash_map->size = 0;
    hash_map->list_size = 8;
    hash_map->hash_func = hash_func == NULL ? default_hash_func : hash_func;
    hash_map->equal_func = equal_func == NULL ? default_equal_func : equal_func;
    hash_map->exists_func = default_exists_func;
    hash_map->get_func = default_get_func;
    hash_map->put_func = default_put_func;
    hash_map->remove_func = default_remove_func;
    hash_map->clear_func = default_clear;

    hash_map->list = NEW_ENTRY_LIST(8);
    if (hash_map->list == NULL) {
        free(hash_map);
        return NULL;
    }
    struct entry *p = hash_map->list;
    for (int i = 0; i < hash_map->list_size; i++) {
        p[i].key = p[i].value = p[i].next = NULL;
    }

    return hash_map;
}

static struct hash_map_iterator *create_hash_map_iterator(struct hash_map *hash_map) {
    struct hash_map_iterator *iterator = NEW_HASH_MAP_ITERATOR();
    if (iterator == NULL) {
        return NULL;
    }

    iterator->hash_map = hash_map;
    iterator->count = 0;
    iterator->hash_code = -1;
    iterator->entry = NULL;

    return iterator;
}

static u_int8_t has_next_hash_map_iterator(struct hash_map_iterator *iterator) {
    return iterator->count < iterator->hash_map->size ? 1 : 0;
}

static struct hash_map_iterator *next_hash_map_iterator(struct hash_map_iterator *iterator) {
    if (has_next_hash_map_iterator(iterator) == 1) {
        if (iterator->entry != NULL && iterator->entry->next != NULL) {
            iterator->count++;
            iterator->entry = iterator->entry->next;
            return iterator;
        }

        while (++iterator->hash_code < iterator->hash_map->list_size) {
            struct entry *entry = &iterator->hash_map->list[iterator->hash_code];
            if (entry->key != NULL) {
                iterator->count++;
                iterator->entry = entry;
                break;
            }
        }
    }

    return iterator;
}

static void free_hash_map_iterator(struct hash_map_iterator **iterator) {
    free(*iterator);
    *iterator = NULL;
}

// 重置
static void reset_hash_map(struct hash_map *hash_map, int list_size) {
    if (list_size < 8) {
        return;
    }

    struct entry *tmp_entry_list = NEW_ENTRY_LIST(hash_map->size);

    struct hash_map_iterator *iterator = create_hash_map_iterator(hash_map);
    int32_t length = hash_map->size;

    for (int index = 0; has_next_hash_map_iterator(iterator) != 0; index++) {
        iterator = next_hash_map_iterator(iterator);
        tmp_entry_list[index].key = iterator->entry->key;
        tmp_entry_list[index].value = iterator->entry->value;
        tmp_entry_list[index].next = NULL;
    }

    free_hash_map_iterator(&iterator);

    hash_map->size = 0;
    for (int i = 0; i < hash_map->list_size; i++) {
        struct entry *current = &hash_map->list[i];
        current->key = NULL;
        current->value = NULL;

        while (current->next != NULL) {
            struct entry *temp = current->next->next;
            free(current->next);
            current->next = temp;
        }
    }

    // 修改内存大小
    hash_map->list_size = list_size;
    struct entry *relist = (struct entry *) realloc(hash_map->list, hash_map->list_size * sizeof(struct entry));
    if (relist != NULL) {
        hash_map->list = relist;
        relist = NULL;
    }

    // 初始化数据
    for (int i = 0; i < hash_map->list_size; i++) {
        hash_map->list[i].key = NULL;
        hash_map->list[i].value = NULL;
        hash_map->list[i].next = NULL;
    }

    for (int i = 0; i < length; i++) {
        hash_map->put_func(hash_map, tmp_entry_list[i].key, tmp_entry_list[i].value);
    }

    free(tmp_entry_list);
}

#endif //TJVMTEST_HASH_MAP_H
