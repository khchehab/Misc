#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"

static char* error = NULL;

int key_exists(map* map, int key);

/*
 * Initializes a map of integer key/value pairs with the specified size.
 */
map* init_map(int size) {
    map* map = malloc(sizeof(map));
    map->count = 0;
    map->size = size;
    map->entries = malloc(size * sizeof(entry));
    error = NULL;
    return map;
}

/*
 * Free the map from memory.
 * This must be called at the end if a map is initialized.
 */
void free_map(map* map) {
    if(map == NULL) {
        error = "Map pointer is NULL";
        return;
    }

    free(map->entries);
    map->count = 0;
    map->size = 0;
    map->entries = NULL;
    free(map);
    error = NULL;
}

/*
 * Inserts a pair to the specified map.
 * It will return true if inserted, and false otherwise.
 */
bool insert_entry(map* map, int key, int value) {
    // check if map pointer is null
    if(map == NULL) {
        error = "Map pointer is NULL";
        return false;
    }

    // check if entries pointer is null
    if(map->entries == NULL) {
        error = "Entries pointer is NULL";
        return false;
    }

    // check if there are no more spaces for the entry
    if(map->count >= map->size) {
        error = "There is no more space for a new entry";
        return false;
    }

    // check if key exists
    if(key_exists(map, key) > -1) {
        error = "The key already exists";
        return false;
    }

    (map->entries + map->count)->key = key;
    (map->entries + map->count)->value = value;
    map->count++;
    error = NULL;

    return true;
}

/*
 * Removes a pair from the speicified map by its key.
 * It will return true if removed, and false otherwise.
 */
bool remove_entry(map* map, int key) {
    // todo implement me
    // watch out for removing an entry in the middle of the pointer, in to reallocate or something to not have an empty memory location of something
    error = NULL;

    return true;
}

/*
 * Get the value of the specified key from the map.
 */
int get(map* map, int key) {
    // todo see if it is better to return pointer to the value here
    // for error handling if key does not exist, the maybe return NULL and if exist return a pointer to it
    // but then it is returning a pointer so it might cause issues for use of changing or something
    // study the idea and see its feasiability and which is better.

    return 0;
}

/*
 * Prints the map to the console.
 */
void print_map(map* map) {
    if(map == NULL || map->entries == NULL || map->size < 1 || map->count < 1) {
        return;
    }

    printf("Map has %d entries out of %d\n", map->count, map->size);
    printf(" ------- -------\n");
    printf("| %-5s | %-5s |\n", "key", "value");
    printf(" ------- -------\n");

    for(int i = 0; i < map->count; ++i) {
        printf("| %-5d | %-5d |\n", (map->entries+i)->key, (map->entries+i)->value);
    }
    printf(" ------- -------\n");
    error = NULL;
}

/*
 * Returns an error text if the last operation failed for some reason.
 * If another operation was done, previous operation's error text will not persist.
 */
char* map_error() {
    return error;
}

/* Private Function */

// returns the index of the key in the entries.
// assumption: map and map->entries are not NULL.
int key_exists(map* map, int key) {
    for(int i = 0; i < map->count; i++) {
        if((map->entries + i)->key == key) {
            return i;
        }
    }

    return -1;
}
