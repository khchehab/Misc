#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "map.h"

#define initial_size 10
#define increments 10

static char* error = NULL;

int key_exists(map* map, int key);

/*
 * Initializes a map of integer key/value pairs.
 */
map* init_map() {
    map* map = malloc(sizeof(map));
    map->count = 0;
    map->size = initial_size; // initial size
    map->entries = malloc(map->size * sizeof(entry));
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

    // check if key exists
    if(key_exists(map, key) > -1) {
        error = "The key already exists";
        return false;
    }

    // check if there are no more spaces for the entry, then increase the entries size
    if(map->count >= map->size) {
        entry* tmp = realloc(map->entries, (map->size + increments) * sizeof(entry));

        if(tmp == NULL) {
            error = "Could not increase entries size";
            return false;
        }

        map->entries = tmp;
        map->size += increments;
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

    int index = key_exists(map, key);

    // check if key exists
    if(index < 0) {
        error = "The key does not exist";
        return false;
    }

    memmove(map->entries + index, map->entries + index + 1, (map->count - index + 1) * sizeof(entry));
    map->count--;

    // after removing the entry and decrementing the count, if there is a multiple of increments free,
    // reallocate the array
    if(map->count % increments == 0) {
        entry* tmp = realloc(map->entries, (map->size - increments) * sizeof(entry));

        if(tmp == NULL) {
            error = "Could not decrease entries size";
            return true; // if we could not decrease the entries size, it is fine, we still have more memory for later on
        }

        map->entries = tmp;
        map->size -= increments;
    }

    error = NULL;
    return true;
}

/*
 * Get the value of the specified key from the map.
 */
bool get_value(map* map, int key, int* value) {
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

    int index = key_exists(map, key);

    // check if key exists
    if(index < 0) {
        error = "The key does not exist";
        return false;
    }

    *value = (map->entries + index)->value;
    error = NULL;
    return true;
}

/*
 * Prints the map to the console.
 */
void print_map(map* map) {
    if(map == NULL || map->entries == NULL) {
        return;
    }

    if(map->size < 1 || map->count < 1) {
        printf("Map is empty\n");
        return;
    }

    #ifdef DEBUG
    printf("--DEBGUG--address of map: %ul, address of entries: %ul, size: %d and count: %d\n", map, map->entries, map->size, map->count);
    #endif

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
