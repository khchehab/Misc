#ifndef __GENERIC_MAP_H__
#define __GENERIC_MAP_H__

#define DEFINE_MAP(prefix, key_type, value_type) \
typedef struct ## prefix ## _entry {             \
    key_type key;                                \
    value_type value;                            \
} ## prefix ## _entry;                           \
                                                 \
typedef struct ## prefix ## _map {               \
    ## prefix ## _entry* entries;                \
    int size;                                    \
    int count;                                   \
};                                               \
                                                 \
// map* init_map(int size) {
//     map* map = malloc(sizeof(map));
//     map->count = 0;
//     map->size = size;
//     map->entries = malloc(size * sizeof(entry));
//     error = NULL;
//     return map;
// }

#endif // __GENERIC_MAP_H__