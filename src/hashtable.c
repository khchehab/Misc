#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"

unsigned int hash(hash_table* ht, int key);
hash_entry* hash_entry_init(int key, int value);
void hash_entry_free(hash_entry* entry);

hash_table* hash_table_init(int size) {
    hash_table* ht = malloc(sizeof(hash_table));
    ht->size = size;
    ht->entries = malloc(ht->size * sizeof(hash_entry*));
    for(int i = 0; i < ht->size; ++i) {
        ht->entries[i] = NULL;
    }
    
    return ht;
}

void hash_table_free(hash_table* ht) {
    for(int i = 0; i < ht->size; ++i) {
        hash_entry_free(ht->entries[i]);
    }

    free(ht->entries);
    ht->entries = NULL;
    ht->size = 0;
    free(ht);
    ht = NULL;
}

bool hash_table_insert(hash_table* ht, int key, int value) {
    if(ht == NULL || ht->entries == NULL) {
        return false;
    }

    // the hash value returned will be the index in memory to store this entry in.
    unsigned int hash_value = hash(ht, key);
    hash_entry* bucket = ht->entries[hash_value];

    // if the memory at hash_value is empty, put the pair.
    if(bucket == NULL) {
        ht->entries[hash_value] = hash_entry_init(key, value);
    } else {
        hash_entry* prev;

        // if there is an entry in memory at hash_value, we need to search for the specified key at the entry.
        do {
            if(bucket->key == key) {
                bucket->value = value;
                return true;
            }

            prev = bucket;
            bucket = bucket->next;
        } while(bucket != NULL);

        // at this point, no key were found, so we add to the next of the current bucket pointer.
        prev->next = hash_entry_init(key, value);
    }

    return true;
}

bool hash_table_get(hash_table* ht, int key, int* value) {
    if(ht == NULL || ht->entries == NULL) {
        return false;
    }

    // the hash value returned will be the index in memory get the key's value.
    unsigned int hash_value = hash(ht, key);
    hash_entry* bucket = ht->entries[hash_value];

    // if bucket is null, then the key does not exist.
    if(bucket == NULL) {
        return false;
    }

    hash_entry* prev;
    do {
        if(bucket->key == key) {
            *value = bucket->value;
            return true;
        }

        prev = bucket;
        bucket = bucket->next;
    } while(bucket != NULL);
    
    // if the while loop finishes, it means the key wasn't found, so no value was retrieved.
    return false;
}

bool hash_table_remove(hash_table* ht, int key) {
    if(ht == NULL || ht->entries == NULL) {
        return false;
    }

    // the hash value returned will be the index in memory to remove this entry.
    unsigned int hash_value = hash(ht, key);
    hash_entry* bucket = ht->entries[hash_value];

    // if bucket is null, then the key does not exist.
    if(bucket == NULL) {
        return false;
    }

    hash_entry* prev = NULL;
    do {
        if(bucket->key == key) {
            if(prev == NULL) {
                ht->entries[hash_value] = bucket->next;
            } else {
                prev->next = bucket->next;
            }
            
            free(bucket);
            return true;
        }

        prev = bucket;
        bucket = bucket->next;
    } while(bucket != NULL);

    // if the while loop finishes, it means the key wasn't found, so nothing was removed.
    return false;
}

void hash_table_print(hash_table* ht) {
    if(ht == NULL || ht->entries == NULL) {
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
    for(int i = 0; i < ht->size; ++i) {
        curr = ht->entries[i];

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

unsigned int hash(hash_table* ht, int key) {
    return key % ht->size;
}

// Create an entry for the hash table.
hash_entry* hash_entry_init(int key, int value) {
    hash_entry* entry = malloc(sizeof(hash_entry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

// Free the hash entry and its next elements.
void hash_entry_free(hash_entry* entry) {
    if(entry != NULL && entry->next != NULL) {
        hash_entry_free(entry->next);
        entry->next = NULL;
    }

    free(entry);
}
