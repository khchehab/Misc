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

    hash_table_free(hash_table);

    return 0;
}
