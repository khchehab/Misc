#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

typedef struct hash_entry {
    int key;
    int value;
    struct hash_entry* next;
} hash_entry;

typedef struct hash_table {
    int size;
    hash_entry** entries;
} hash_table;

hash_table* hash_table_init(int size);
void hash_table_free(hash_table* ht);

_Bool hash_table_insert(hash_table* ht, int key, int value);
_Bool hash_table_get(hash_table* ht, int key, int* value);
_Bool hash_table_remove(hash_table* ht, int key);
void hash_table_print(hash_table* ht);

#endif // __HASHTABLE_H__