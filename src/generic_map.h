#ifndef __GENERIC_MAP_H__
#define __GENERIC_MAP_H__

#define DEFINE_MAP(prefix, key_type, value_type)                \
typedef struct prefix ## _entry {                               \
    key_type key;                                               \
    value_type value;                                           \
} prefix ## _entry;                                             \
                                                                \
typedef struct prefix ## _map {                                 \
    prefix ## _entry* entries;                                  \
    int size;                                                   \
    int count;                                                  \
} prefix ## _map;                                               \
                                                                \
prefix ## _map* init_ ## prefix ## _map(int size) {             \
    prefix ## _map* map = malloc(sizeof(prefix ## _map));       \
    map->count = 0;                                             \
    map->size = size;                                           \
    map->entries = malloc(size * sizeof(prefix ## _entry));     \
    return map;                                                 \
}                                                               \
                                                                \
void free_ ## prefix ## _map(prefix ## _map* map) {             \
    if(map == NULL) {                                           \
        return;                                                 \
    }                                                           \
                                                                \
    free(map->entries);                                         \
    map->count = 0;                                             \
    map->size = 0;                                              \
    map->entries = NULL;                                        \
    free(map);                                                  \
}

#endif // __GENERIC_MAP_H__