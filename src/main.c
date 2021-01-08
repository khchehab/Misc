#include "hashtable.h"

int main(int argc, char* argv[]) {
    hash_table* hash_table = hash_table_init(6);

    hash_table_insert(hash_table, 1, 34);
    hash_table_insert(hash_table, 2, 44);
    hash_table_insert(hash_table, 3, 52);
    hash_table_insert(hash_table, 4, 56);
    hash_table_insert(hash_table, 5, 178);
    hash_table_insert(hash_table, 6, 23);
    hash_table_print(hash_table);

    hash_table_free(hash_table);

    return 0;
}
