#ifndef __SIMPLE_MAP_H__
#define __SIMPLE_MAP_H__

typedef struct entry_t {
    int key;
    char* value;
} entry_t;

typedef struct map_t {
    int size;
    int count;
    entry_t* entries;
} map_t;

map_t* map_init();
void map_free(map_t* map);

_Bool map_put(map_t* map, int key, char* value);
_Bool map_remove(map_t* map, int key);
const char* map_get(map_t* map, int key);
_Bool map_key_exists(map_t* map, int key);
void map_print(map_t* map);

#endif // __SIMPLE_MAP_H__