#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "map.h"

#define INITIAL_SIZE 10
#define MAP_ENTRY_INCREMENTS 10

static int map_key_index(map_t* map, int key);
static bool map_grow(map_t* map, int new_size);
static bool map_shrink(map_t* map, int new_size);

// Map Functions

/*
 * Initialize the map.
 */
map_t map_init() {
    map_t map;
    map_clear(&map);
    return map;
}

/*
 * Free the map entries from memory.
 */
void map_free(map_t* map) {
    free(map->entries);
}

/*
 * Reset the map to its initial state.
 */
void map_clear(map_t* map) {
    map->size = INITIAL_SIZE;
    map->count = 0;

    // free the current entries memory
    if(map->entries != NULL) {
        free(map->entries);
    }

    // allocate memory for the entries
    map->entries = malloc(map->size * sizeof(entry_t));
}

/*
 * Checks if a key exists in the map.
 */
bool map_key_exist(map_t* map, int key) {
    return map_key_index(map, key) >= 0;
}

/*
 * Adds an entry consisting of the specified key/value pair.
 */
bool map_put(map_t* map, int key, int value) {
    if(map == NULL || map->entries == NULL) {
        return false;
    }

    // key exists
    if(map_key_index(map, key) >= 0) {
        return false;
    }

    if(map->count >= map->size) {
        if(map_grow(map, map->size + MAP_ENTRY_INCREMENTS)) {
            return false;
        }
    }

    map->entries[map->count].key = key;
    map->entries[map->count].value = value;
    map->count++;

    return true;
}

/*
 * Removes the entry from map that has the specified key.
 */
bool map_remove(map_t* map, int key) {
    if(map == NULL || map->entries == NULL) {
        return false;
    }

    int index = map_key_index(map, key);
    
    // if key doesn't exist
    if(index < 0) {
        return false;
    }

    // shift the entries back at the index
    memmove(map->entries + index, map->entries + index + 1, (map->count - index - 1) * sizeof(entry_t));
    map->count--;

    if(map->count > 0 && map->count % MAP_ENTRY_INCREMENTS == 0) {
        if(!map_shrink(map, map->size - MAP_ENTRY_INCREMENTS)) {
            return false;
        }
    }

    return true;
}

/*
 * Returns the value of the specified key.
 */
int map_get(map_t* map, int key) {
    int index = map_key_index(map, key);
    return index >= 0 ? map->entries[index].value : -1;
}

/*
 * Prints the map to the console.
 */
void map_print(map_t* map) {
    if(map == NULL || map->entries == NULL) {
        printf("Map is not defined!\n");
        return;
    }

    if(map->size == 0 || map->count == 0) {
        printf("Map is empty!\n");
        return;
    }

    printf("Map has size of %d with a count of %d\n", map->size, map->count);
    printf(" ---------------------------------------------\n");
    printf("| %-20s | %-20s |\n", "key", "value");
    printf(" ---------------------------------------------\n");

    for(int i = 0; i < map->count; i++) {
        printf("| %-20d | %-20d |\n", map->entries[i].key, map->entries[i].value);
    }

    printf(" ---------------------------------------------\n\n");
}

// Helper Functions

int map_key_index(map_t* map, int key) {
    if(map == NULL || map->entries == NULL || map->count == 0 || map->size == 0) {
        return -1;
    }

    for(int i = 0; i < map->count; i++) {
        if(map->entries[i].key == key) {
            return i;
        }
    }

    return -1;
}

bool map_grow(map_t* map, int new_size) {
    entry_t* tmp = realloc(map->entries, new_size * sizeof(entry_t));
    if(tmp == NULL) {
        // could not increase entries list, so can't add the new entry
        return false;
    }

    map->size = new_size;
    map->entries = tmp;

    return true;
}

bool map_shrink(map_t* map, int new_size) {
    entry_t* tmp = realloc(map->entries, new_size * sizeof(entry_t));
    
    // if the list was not reallocated, it's fine since it means we have more memory allocated
    if(tmp != NULL) {
        map->size = new_size;
        map->entries = tmp;
    }

    return true;
}
