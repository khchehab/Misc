#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"

// typedef struct hash_entry {
//     int key;
//     int value;
//     hash_entry* next;
// } hash_entry;

// typedef struct hash_table {
//     int size;
//     hash_entry** entries;
// } hash_table;

unsigned int hash(hash_table* hash_table, int key);
hash_entry* hash_entry_init(int key, int value);
void hash_entry_free(hash_entry* hash_entry);

hash_table* hash_table_init(int size) {
    hash_table* hash_table = malloc(sizeof(hash_table));
    hash_table->size = size;
    hash_table->entries = malloc(hash_table->size * sizeof(hash_entry*));
    for(int i = 0; i < hash_table->size; ++i) {
        hash_table->entries[i] = NULL;
    }
    
    return hash_table;
}

void hash_table_free(hash_table* hash_table) {
    for(int i = 0; i < hash_table->size; ++i) {
        hash_entry_free(hash_table->entries[i]);
    }

    free(hash_table->entries);
    hash_table->entries = NULL;
    hash_table->size = 0;
    free(hash_table);
    hash_table = NULL;
}

bool hash_table_insert(hash_table* hash_table, int key, int value) {
    if(hash_table == NULL || hash_table->entries == NULL) {
        return false;
    }

    // the hash value returned will be the index in memory to store this key in
    unsigned int hash_value = hash(hash_table, key);
    hash_entry* bucket = hash_table->entries[hash_value];

    // if the memory at hash_value is empty, put the pair
    if(bucket == NULL) {
        hash_table->entries[hash_value] = hash_entry_init(key, value);
    } else {
        hash_entry* prev;

        // if there is an entry in memory at hash_value, we need to search for the specified key at the entry
        do {
            if(bucket->key == key) {
                bucket->value = value;
                return true;
            }

            prev = bucket;
            bucket = bucket->next;
        } while(bucket != NULL);

        // at this point, no key were found, so we add to the next of the current bucket pointer
        prev->next = hash_entry_init(key, value);
    }

    return true;
}

bool hash_table_get(hash_table* hash_table, int key) {
    return true;
}

bool hash_table_remove(hash_table* hash_table, int key) {
    return true;
}

void hash_table_print(hash_table* hash_table) {
    if(hash_table == NULL || hash_table->entries == NULL) {
        printf("The hash table is empty");
        return;
    }

    #ifdef DEBUG
    printf("     ");
    #endif

    printf(" ------- -------\n");

    #ifdef DEBUG
    printf("     ");
    #endif

    printf("| %-5s | %-5s |\n", "key", "value");

    #ifdef DEBUG
    printf("     ");
    #endif

    printf(" ------- -------\n");

    hash_entry* curr;
    for(int i = 0; i < hash_table->size; ++i) {
        curr = hash_table->entries[i];

        #ifdef DEBUG
        if(curr == NULL) {
            printf("%-5d| %-5s | %-5s |\n", i, "-", "-");
        }
        #endif

        while(curr != NULL) {
            #ifdef DEBUG
                printf("%-5d", i);
            #endif

            printf("| %-5d | %-5d |\n", curr->key, curr->value);
            curr = curr->next;
        }
    }

    #ifdef DEBUG
    printf("     ");
    #endif

    printf(" ------- -------\n");
}

// Hash function
unsigned int hash(hash_table* hash_table, int key) {
    return key % hash_table->size;
}

// Create an entry for the hash table
hash_entry* hash_entry_init(int key, int value) {
    hash_entry* hash_entry = malloc(sizeof(hash_entry));
    hash_entry->key = key;
    hash_entry->value = value;
    hash_entry->next = NULL;
    return hash_entry;
}

void hash_entry_free(hash_entry* hash_entry) {
    if(hash_entry != NULL) {
        hash_entry_free(hash_entry->next);
        free(hash_entry->next);
    }
}
