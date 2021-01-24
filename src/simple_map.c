#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "simple_map.h"

#define MAP_ENTRIES_INCREMENTS 10

static int map_key_index(map_t* map, int key);

map_t* map_init() {
    map_t* map = malloc(sizeof(map_t));
    map->size = MAP_ENTRIES_INCREMENTS;
    map->count = 0;
    map->entries = malloc(map->size * sizeof(entry_t));
    return map;
}

void map_free(map_t* map) {
    if(map == NULL) {
        return;
    }
    
    free(map->entries);
    map->entries = NULL;
    free(map);
}

bool map_put(map_t* map, int key, char* value) {
    if(map == NULL || map->entries == NULL) {
        return false;
    }

    // increase size of memory of entries list
    if(map->count >= map->size) {
        entry_t* tmp = realloc(map->entries, (map->size + MAP_ENTRIES_INCREMENTS) * sizeof(entry_t));

        if(tmp == NULL) {
            // could not increase list size, so can't add the entry
            return false;
        }

        map->size += MAP_ENTRIES_INCREMENTS;
        map->entries = tmp;
    }

    (map->entries + map->count)->key = key;
    (map->entries + map->count)->value = value;
    map->count++;

    return true;
}

bool map_remove(map_t* map, int key) {
    if(map == NULL || map->entries == NULL) {
        return false;
    }

    int index = map_key_index(map, key);
    
    // key does not exist
    if(index < 0) {
        return false;
    }

    // shift the entries back
    memmove(map->entries + index, map->entries + index + 1, (map->count - index - 1) * sizeof(entry_t));
    map->count--;

    // after decrementing the counter, if there is more than enough space
    // reduce them
    if(map->count > 0 && map->count % MAP_ENTRIES_INCREMENTS == 0) {
        entry_t* tmp = realloc(map->entries, (map->size - MAP_ENTRIES_INCREMENTS) * sizeof(entry_t));

        if(tmp == NULL) {
            // could not decrease list size, but still the entry was removed
            return true;
        }

        map->size -= MAP_ENTRIES_INCREMENTS;
        map->entries = tmp;
    }

    return true;
}

const char* map_get(map_t* map, int key) {
    if(map == NULL || map->entries == NULL) {
        return NULL;
    }

    int index = map_key_index(map, key);
    return index < 0 ? NULL : (map->entries + index)->value;
}

bool map_key_exists(map_t* map, int key) {
    if(map == NULL || map->entries == NULL) {
        return false;
    }

    return map_key_index(map, key) >= 0;
}

void map_print(map_t* map) {
    if(map == NULL || map->entries == NULL) {
        printf("Map is NULL!\n");
        return;
    }

    if(map->count == 0 || map->size == 0) {
        printf("Map is empty!\n");
        return;
    }

    printf("Map is of size %d but has %d element(s)\n", map->size, map->count);
    printf(" ------------------------------ \n");
    printf("| %-5s | %-20s |\n", "key", "value");
    printf(" ------------------------------ \n");
    
    for(int i = 0; i < map->count; i++) {
        printf("| %-5d | %-20s |\n", (map->entries + i)->key, (map->entries + i)->value);
    }
    printf(" ------------------------------ \n\n");
}

int map_key_index(map_t* map, int key) {
    // assumption: map and map->entries are not NULL
    for(int i = 0; i < map->count; i++) {
        if((map->entries + i)->key == key) {
            return i;
        }
    }

    return -1;
}
