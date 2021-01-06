#ifndef __HASHMAP_H__
#define __HASHMAP_H__

typedef struct hash_entry {
    int key;
    int value;
    hash_entry* next;
} hash_entry;

typedef struct hash_map {
    int size;
    hash_entry** entries;
} hash_map;

hash_map* hash_map_init();
void hash_map_free(hash_map* hash_map);

_Bool hash_map_put(hash_map* hash_map, int key, int value);
_Bool hash_map_get(hash_map* hash_map, int key);
_Bool hash_map_remove(hash_map* hash_map, int key);
void hash_map_print(hash_map* hash_map);

#endif // __HASHMAP_H__