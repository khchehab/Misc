#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ---------------------------------------------------- //

#define INITIAL_SIZE 10
#define MAP_ENTRY_INCREMENTS 10

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

}

// value exist - optional
// get
// put
// remove by key
// print
// helper functions for growing and shrinking

// ---------------------------------------------------- //

int main(int argc, char* argv[]) {
    return 0;
}
