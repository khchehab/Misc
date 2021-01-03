#include <stdio.h>
#include "map.h"

int main(int argc, char* argv[]) {
    map* map = init_map(3);

    insert_entry(map, 1, 42);
    insert_entry(map, 2, 44);
    insert_entry(map, 3, 50);

    print_map(map);

    free_map(map);

    return 0;
}