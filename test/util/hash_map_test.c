//
// Created by tairy on 2020/11/20.
//
#include "stdio.h"
#include "util/hash_map.h"

int main() {
    struct hash_map *hash_map = create_hash_map(NULL, NULL);
    default_put_func(hash_map, "key", "value");
    default_put_func(hash_map, "key1", "value1");
    default_put_func(hash_map, "key2", "value2");
    default_put_func(hash_map, "key3", "value3");
    default_put_func(hash_map, "key4", "value4");
    default_put_func(hash_map, "key5", "value5");
    default_put_func(hash_map, "key6", "value6");
    default_put_func(hash_map, "key7", "value7");
    default_put_func(hash_map, "key8", "value8");
    default_put_func(hash_map, "key9", "value9");
    default_remove_func(hash_map, "key3");

    struct hash_map_iterator *iterator = create_hash_map_iterator(hash_map);

    for (int index = 0; has_next_hash_map_iterator(iterator) != 0; index++) {
        iterator = next_hash_map_iterator(iterator);
        printf("key:%s, value:%s, hash_code: %d\n", iterator->entry->key, iterator->entry->value,
               default_hash_func(hash_map, iterator->entry->key));
    }

    printf("result: %s, size: %d, list_size: %d\n", default_get_func(hash_map, "key"), hash_map->size,
           hash_map->list_size);

    free_hash_map_iterator(&iterator);
    return 0;
}