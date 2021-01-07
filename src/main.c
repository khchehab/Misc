#include <stdio.h>
#include "hashtable.h"

int main(int argc, char* argv[]) {
    hash_table* hash_table = hash_table_init(6);

    hash_table_insert(hash_table, 120, 34);
    hash_table_insert(hash_table, 250, 44);
    hash_table_insert(hash_table, 33, 52);
    hash_table_insert(hash_table, 42, 56);
    hash_table_insert(hash_table, 251, 178);
    hash_table_insert(hash_table, 522, 23);
    hash_table_print(hash_table);

    int value;

    if(hash_table_get(hash_table, 42, &value)) {
        printf("Value of key 42 is 56 => %d\n", value);
    } else {
        printf("key 42 is not found\n");
    }

    if(hash_table_get(hash_table, 250, &value)) {
        printf("Value of key 250 is 44 => %d\n", value);
    } else {
        printf("key 250 is not found\n");
    }

    if(hash_table_get(hash_table, 22, &value)) {
        printf("Value of key 22 is ??? => %d\n", value);
    } else {
        printf("key 22 is not found\n");
    }

    hash_table_free(hash_table);

    return 0;
}
