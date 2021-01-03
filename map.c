#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"

/*
 * Initializes a map of integer key/value pairs with the specified size.
 */
map* init_map(int size) {
    map* map = malloc(sizeof(map));
    map->count = 0;
    map->size = size;
    map->entries = malloc(size * sizeof(entry));
    return map;
}

/*
 * Free the map from memory.
 * This must be called at the end if a map is initialized.
 */
void free_map(map* map) {
    if(map == NULL) {
        return;
    }

    free(map->entries);
    map->count = 0;
    map->size = 0;
    map->entries = NULL;
    free(map);
}

/*
 * Inserts a pair to the specified map.
 * It will return true if inserted, and false otherwise.
 */
bool insert_entry(map* map, int key, int value) {
    // todo the controls below are separated for later on if error handling and text are implemented to differentiate the errors

    // check if map pointers are not null
    if(map == NULL || map->entries == NULL) {
        return false;
    }

    // check if there are no more spaces for the entry
    if(map->count >= map->size) {
        return false;
    }

    // todo handle if key exist

    map->count++;
    (map->entries + map->count)->key = key;
    (map->entries + map->count)->value = value;

    return true;
}

/*
 * Removes a pair from the speicified map by its key.
 * It will return true if removed, and false otherwise.
 */
bool remove_entry(map* map, int key) {
    // todo implement me
    // watch out for removing an entry in the middle of the pointer, in to reallocate or something to not have an empty memory location of something
    return true;
}

/*
 * Prints the map to the console.
 */
void print_map(map* map) {
    if(map == NULL || map->size < 1 || map->count < 1 || map->entries == NULL) {
        return;
    }

    printf("------|------\n");
    printf("%-5s | %-5s\n", "key", "value");
    printf("------|------\n");

    for(int i = 0; i < map->count; ++i) {
        printf("%-5d | %-5d\n", (map->entries+i)->key, (map->entries+i)->value);
    }
    printf("------|------\n");
}
