#ifndef __GENERIC_MAP_H__
#define __GENERIC_MAP_H__

/*
 * Below are macros to define the header and source of a map by supplying the below information:
 * 1. prefix: the prefix for the map, it will be <prefix>_map_t.
 * 2. key_type: the type of the key (eg. const char*).
 * 3. value_type: the type of the value (eg. int).
 * 4. key_name: the name of the key field.
 * 5. value_name: the name of the value field.
 * 6. get_value_type: the type for the get function. This get function should return a pointer,
 *    so if value_type is a pointer in it of itself, here it should be supplied without asterisk
 *    since it will be added automatically.
 * 
 * Pre-Requisite:
 * 1. Before calling the source macro in the source file, a function that compares keys must exist
 *    with the following prototype:
 *    static bool <prefix>_map_key_equals(key_type a, key_type b);
 * 
 *    Without this function, it will not work. So it must be defined prior to calling GENERIC_MAP_SOURCE.
 *    THIS IS VERY IMPORTANT!!!
 *
 * 2. Include all the needed headers (especially structs are used as either key type or value type).
 * 3. This is kind of a weird one, but if the value type is a pointer to something, the get function
 *    must return the value as it is (and not the address of it), otherwise if value type is not a pointer,
 *    since the function returns a pointer, we need to return the address of the value.
 *    For this, we use the macro RETURN_OF_VALUE, which must be defined in the source file as either empty
 *    for pointer value types and `&` for non-pointer value types.
 */

#define GENERIC_MAP_HEADER(prefix, key_type, value_type, key_name, value_name, get_value_type)  \
    typedef struct prefix ## _entry_t {                                                         \
        key_type key_name;                                                                      \
        value_type value_name;                                                                  \
    } prefix ## _entry_t;                                                                       \
                                                                                                \
    typedef struct prefix ## _map_t {                                                           \
        int size;                                                                               \
        int count;                                                                              \
        prefix ## _entry_t* entries;                                                            \
    } prefix ## _map_t;                                                                         \
                                                                                                \
    /*
     * Initializes the map.
     */                                                                                         \
    prefix ## _map_t prefix ## _map_init();                                                     \
                                                                                                \
    /*
     * Free the map.
     */                                                                                         \
    void prefix ## _map_free(prefix ## _map_t* map);                                            \
                                                                                                \
    /*
     * Checks if key exist.
     */                                                                                         \
    bool prefix ## _map_key_exist(prefix ## _map_t* map, key_type key_name);                    \
                                                                                                \
    /*
     * Adds an entry.
     */                                                                                         \
    void prefix ## _map_put(prefix ## _map_t* map, key_type key_name, value_type value_name);   \
                                                                                                \
    /*
     * Removes an entry.
     */                                                                                         \
    void prefix ## _map_remove(prefix ## _map_t* map, key_type key_name);                       \
                                                                                                \
    /*
     * Returns the value of the specified key. 
     */                                                                                         \
    get_value_type* prefix ## _map_get(prefix ## _map_t* map, key_type key_name);               \

#define GENERIC_MAP_SOURCE(prefix, key_type, value_type, key_name, value_name, get_value_type)                          \
    static const int prefix ## _map_initial_size = 10;                                                                  \
    static const int prefix ## _map_entry_increments = 10;                                                              \
                                                                                                                        \
    static int prefix ## _map_index(prefix ## _map_t* map, key_type key_name);                                          \
    static bool prefix ## _map_grow(prefix ## _map_t* map, int new_size);                                               \
    static bool prefix ## _map_shrink(prefix ## _map_t* map, int new_size);                                             \
                                                                                                                        \
    /*
     * Initializes the map.
     */                                                                                                                 \
    prefix ## _map_t prefix ## _map_init() {                                                                            \
        prefix ## _map_t map;                                                                                           \
        map.size = prefix ## _map_initial_size;                                                                         \
        map.count = 0;                                                                                                  \
        map.entries = malloc(map.size * sizeof(prefix ## _entry_t));                                                    \
        return map;                                                                                                     \
    }                                                                                                                   \
                                                                                                                        \
    /*
     * Free the map.
     */                                                                                                                 \
    void prefix ## _map_free(prefix ## _map_t* map) {                                                                   \
        if(map->entries != NULL) {                                                                                      \
            free(map->entries);                                                                                         \
        }                                                                                                               \
    }                                                                                                                   \
                                                                                                                        \
    /*
     * Checks if key exist.
     */                                                                                                                 \
    bool prefix ## _map_key_exist(prefix ## _map_t* map, key_type key_name) {                                          \
        return prefix ## _map_index(map, key_name) >= 0;                                                                \
    }                                                                                                                   \
                                                                                                                        \
    /*
     * Adds an entry.
     */                                                                                                                 \
    void prefix ## _map_put(prefix ## _map_t* map, key_type key_name, value_type value_name) {                          \
        if(map == NULL || map->entries == NULL) {                                                                       \
            return;                                                                                                     \
        }                                                                                                               \
                                                                                                                        \
        /* if key exist */                                                                                              \
        if(prefix ## _map_index(map, key_name) >= 0) {                                                                  \
            return;                                                                                                     \
        }                                                                                                               \
                                                                                                                        \
        if(map->count >= map->size) {                                                                                   \
            if(!prefix ## _map_grow(map, map->size + prefix ## _map_entry_increments)) {                                \
                return;                                                                                                 \
            }                                                                                                           \
        }                                                                                                               \
                                                                                                                        \
        map->entries[map->count].key_name = key_name;                                                                   \
        map->entries[map->count].value_name = value_name;                                                               \
        map->count++;                                                                                                   \
    }                                                                                                                   \
                                                                                                                        \
    /*
     * Removes an entry.
     */                                                                                                                 \
    void prefix ## _map_remove(prefix ## _map_t* map, key_type key_name) {                                              \
        if(map == NULL || map->entries == NULL) {                                                                       \
            return;                                                                                                     \
        }                                                                                                               \
                                                                                                                        \
        int index = prefix ## _map_index(map, key_name);                                                                \
                                                                                                                        \
        /* if key doesn't exist */                                                                                      \
        if(index < 0) {                                                                                                 \
            return;                                                                                                     \
        }                                                                                                               \
                                                                                                                        \
        memmove(map->entries + index, map->entries + index + 1, (map->count - index - 1) * sizeof(prefix ## _entry_t)); \
        map->count--;                                                                                                   \
                                                                                                                        \
        if(map->count > 0 && map->count % prefix ## _map_entry_increments == 0) {                                       \
            prefix ## _map_shrink(map, map->size - prefix ## _map_entry_increments);                                    \
        }                                                                                                               \
    }                                                                                                                   \
                                                                                                                        \
    /*
     * Returns the value of the specified key.
     */                                                                                                                 \
    get_value_type* prefix ## _map_get(prefix ## _map_t* map, key_type key_name) {                                      \
        int index = prefix ## _map_index(map, key_name);                                                                \
        return index < 0 ? NULL : RETURN_OF_VALUE map->entries[index].value_name;                                       \
    }                                                                                                                   \
                                                                                                                        \
    /* Helper functions implementation */                                                                               \
                                                                                                                        \
    int prefix ## _map_index(prefix ## _map_t* map, key_type key_name) {                                                \
        if(map == NULL || map->entries == NULL || map->count == 0 || map->size == 0) {                                  \
            return -1;                                                                                                  \
        }                                                                                                               \
                                                                                                                        \
        for(int i = 0; i < map->count; i++) {                                                                           \
            if(prefix ## _map_key_equals(map->entries[i].key_name, key_name)) {                                         \
                return i;                                                                                               \
            }                                                                                                           \
        }                                                                                                               \
                                                                                                                        \
        return -1;                                                                                                      \
    }                                                                                                                   \
                                                                                                                        \
    bool prefix ## _map_grow(prefix ## _map_t* map, int new_size) {                                                     \
        prefix ## _entry_t* tmp = realloc(map->entries, new_size * sizeof(prefix ## _entry_t));                         \
        if(tmp == NULL) {                                                                                               \
            /* could not increase entries list, so we can't add the new entry */                                        \
            return false;                                                                                               \
        }                                                                                                               \
                                                                                                                        \
        map->size = new_size;                                                                                           \
        map->entries = tmp;                                                                                             \
                                                                                                                        \
        return true;                                                                                                    \
    }                                                                                                                   \
                                                                                                                        \
    bool prefix ## _map_shrink(prefix ## _map_t* map, int new_size) {                                                   \
        prefix ## _entry_t* tmp = realloc(map->entries, new_size * sizeof(prefix ## _entry_t));                         \
                                                                                                                        \
        /* if the list was not reallocated, it's fine since it means we have more memory allocated */                   \
        if(tmp != NULL) {                                                                                               \
            map->size = new_size;                                                                                       \
            map->entries = tmp;                                                                                         \
        }                                                                                                               \
                                                                                                                        \
        return true;                                                                                                    \
    }                                                                                                                   \

#endif // __GENERIC_MAP_H__