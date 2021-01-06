#include <stdio.h>
#include <stdbool.h>
#include "hashmap.h"

// typedef struct hash_entry {
//     int key;
//     int value;
//     hash_entry* next;
// } hash_entry;

// typedef struct hash_map {
//     int size;
//     hash_entry** entries;
// } hash_map;

#define SIZE 10

unsigned int hash(hash_map* hash_map, int key);

hash_map* hash_map_init() {
    hash_map* hash_map = malloc(sizeof(hash_map));
    hash_map->size = SIZE;
    hash_map->entries = malloc(hash_map->size * sizeof(hash_entry*));
    for(int i = 0; i < hash_map->size; i++) {
        *(hash_map->entries + i) = NULL;
    }
    
    return hash_map;
}

void hash_map_free(hash_map* hash_map) {
    for(int i = 0; i < hash_map->size; i++) {
        if(*(hash_map->entries + i) != NULL) {
            free(*(hash_map->entries + i));
        }
    }
    free(hash_map->entries);
    hash_map->entries = NULL;
    hash_map->size = 0;
    free(hash_map);
    hash_map = NULL;
}

bool hash_map_put(hash_map* hash_map, int key, int value) {

}

bool hash_map_get(hash_map* hash_map, int key) {

}

bool hash_map_remove(hash_map* hash_map, int key) {

}

void hash_map_print(hash_map* hash_map) {

}

// Hash function
unsigned int hash(hash_map* hash_map, int key) {
    return 0;
}
