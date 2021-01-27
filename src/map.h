#ifndef __MAP_H__
#define __MAP_H__

typedef struct entry_t {
    int key;
    int value;
} entry_t;

typedef struct map_t {
    int size;
    int count;
    entry_t* entries;
} map_t;

/*
 * Initialize the map.
 */
map_t map_init();

/*
 * Free the map entries from memory.
 */
void map_free(map_t* map);

/*
 * Reset the map to its initial state.
 */
void map_clear(map_t* map);

/*
 * Checks if a key exists in the map.
 */
_Bool map_key_exist(map_t* map, int key);

/*
 * Adds an entry consisting of the specified key/value pair.
 */
_Bool map_put(map_t* map, int key, int value);

/*
 * Removes the entry from map that has the specified key.
 */
_Bool map_remove(map_t* map, int key);

/*
 * Returns the value of the specified key.
 */
int map_get(map_t* map, int key);

/*
 * Prints the map to the console.
 */
void map_print(map_t* map);

#endif // __MAP_H__