#include <stdio.h>
#include "map.h"

int main(int argc, char* argv[]) {
    simple_map_t map = simple_map_init();
    simple_map_put(&map, "key1", "value1");
    simple_map_put(&map, "key2", "value2");
    simple_map_put(&map, "key3", "value3");

    for(int i = 0; i < map.count; i++) {
        printf("[%s] => %s\n", map.entries[i].key, map.entries[i].value);
    }

    if(!simple_map_key_exist(&map, "key1")) {
        printf("key1 does not exist\n");
    } else {
        printf("key1 does exist\n");
    }

    if(!simple_map_key_exist(&map, "key42")) {
        printf("key42 does not exist\n");
    } else {
        printf("key42 does exist\n");
    }

    simple_map_free(&map);
    return 0;
}
