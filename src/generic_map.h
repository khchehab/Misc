#ifndef __GENERIC_MAP_H__
#define __GENERIC_MAP_H__

#ifndef ENTRY_INCREMENTS
    #define ENTRY_INCREMENTS 10
#endif

#define DEFINE_MAP(prefix, key_type, value_type)                                                                               \
typedef struct prefix ## _entry {                                                                                              \
    key_type key;                                                                                                              \
    value_type value;                                                                                                          \
} prefix ## _entry;                                                                                                            \
                                                                                                                               \
typedef struct prefix ## _map {                                                                                                \
    prefix ## _entry* entries;                                                                                                 \
    int size;                                                                                                                  \
    int count;                                                                                                                 \
} prefix ## _map;                                                                                                              \
                                                                                                                               \
prefix ## _map* init_ ## prefix ## _map() {                                                                                    \
    prefix ## _map* map = malloc(sizeof(prefix ## _map));                                                                      \
    map->count = 0;                                                                                                            \
    map->size = ENTRY_INCREMENTS;                                                                                              \
    map->entries = malloc(map->size * sizeof(prefix ## _entry));                                                               \
    return map;                                                                                                                \
}                                                                                                                              \
                                                                                                                               \
void free_ ## prefix ## _map(prefix ## _map* map) {                                                                            \
    if(map == NULL) {                                                                                                          \
        return;                                                                                                                \
    }                                                                                                                          \
                                                                                                                               \
    free(map->entries);                                                                                                        \
    map->count = 0;                                                                                                            \
    map->size = 0;                                                                                                             \
    map->entries = NULL;                                                                                                       \
    free(map);                                                                                                                 \
}                                                                                                                              \
                                                                                                                               \
bool insert_ ## prefix ## _entry(prefix ## _map* map, key_type key, value_type value) {                                        \
    if(map == NULL || map->entries == NULL || prefix ## _key_exists(map, key) > -1) {                                          \
        return false;                                                                                                          \
    }                                                                                                                          \
                                                                                                                               \
    if(map->count >= map->size) {                                                                                              \
        prefix ## _entry* tmp = realloc(map->entries, (map->size + ENTRY_INCREMENTS) * sizeof(prefix ## _entry));              \
                                                                                                                               \
        if(tmp == NULL) {                                                                                                      \
            return false;                                                                                                      \
        }                                                                                                                      \
                                                                                                                               \
        map->entries = tmp;                                                                                                    \
        map->size += ENTRY_INCREMENTS;                                                                                         \
    }                                                                                                                          \
                                                                                                                               \
    (map->entries + map->count)->key = key;                                                                                    \
    (map->entries + map->count)->value = value;                                                                                \
    map->count++;                                                                                                              \
                                                                                                                               \
    return true;                                                                                                               \
}                                                                                                                              \
                                                                                                                               \
bool remove_ ## prefix ## _entry(prefix ## _map* map, key_type key, value_type value) {                                        \
    if(map == NULL || map->entries == NULL) {                                                                                  \
        return false;                                                                                                          \
    }                                                                                                                          \
                                                                                                                               \
    int index = prefix ## _key_exists(map, key);                                                                               \
    if(index < 0) {                                                                                                            \
        return false;                                                                                                          \
    }                                                                                                                          \
                                                                                                                               \
    memmove(map->entries + index, map->entries + index + 1, (map->count - index + 1) * sizeof(prefix ## _entry));              \
    map->count;                                                                                                                \
                                                                                                                               \
    /* after removing the entry and decrementing the count, if there is a multiple of increments free, reallocate the array */ \
    if(map->size % ENTRY_INCREMENTS == 0) {                                                                                    \
        prefix ## _entry* tmp = realloc(map->entries, (map->size - ENTRY_INCREMENTS) * sizeof(prefix ## _entry));              \
                                                                                                                               \
        if(tmp == NULL) {                                                                                                      \
            return true; /* if we could not decrease the entries size, it is fine, we still have more memory for later on */   \
        }                                                                                                                      \
                                                                                                                               \
        map->entries = tmp;                                                                                                    \
        map->size -= ENTRY_INCREMENTS;                                                                                         \
    }                                                                                                                          \
                                                                                                                               \
    return true;                                                                                                               \
}                                                                                                                              \
                                                                                                                               \
bool get_ ## prefix ## _value(prefix ## _map* map, key_type key, value_type* value)  {                                         \
    if(map == NULL || map->entries == NULL) {                                                                                  \
        return false;                                                                                                          \
    }                                                                                                                          \
                                                                                                                               \
    int index = prefix ## _key_exists(map, key);                                                                               \
    if(index < 0) {                                                                                                            \
        return false;                                                                                                          \
    }                                                                                                                          \
                                                                                                                               \
    *value = (map->entries + index)->value;                                                                                    \
                                                                                                                               \
    return true;                                                                                                               \
}                                                                                                                              \
                                                                                                                               \
int prefix ## _key_exists(prefix ## _map* map, key_type key) {                                                                 \
    for(int i = 0; i < ma->count; i++) {                                                                                       \
        if((map->entries + i)->key == key) {                                                                                   \
            return i;                                                                                                          \
        }                                                                                                                      \
    }                                                                                                                          \
                                                                                                                               \
    return -1;                                                                                                                 \
}

#endif // __GENERIC_MAP_H__