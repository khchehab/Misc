#include "map.h"

int main(int argc, char* argv[]) {
    map* map = init_map();
    print_map(map);

    insert_entry(map, 1, 42);
    print_map(map);

    for(int i = 0; i < 9; i++) {
        insert_entry(map, i, 42 + ((i+1) * 2));
    }
    print_map(map);

    insert_entry(map, 10, 101);
    print_map(map);

    for(int i = 20; i < 25; i++) {
        insert_entry(map, i, 42 + i);
    }
    print_map(map);

    free_map(map);
    return 0;
}
