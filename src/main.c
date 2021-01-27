#include <stdio.h>
#include "map.h"

int main(int argc, char* argv[]) {
    map_t map = map_init();

    printf("first\n------------\n");
    map_print(&map);

    printf("second\n------------\n");
    map_put(&map, 42, 55);
    map_put(&map, 33, 66);
    map_put(&map, 22, 77);
    map_put(&map, 55, 112);
    map_print(&map);

    printf("third\n------------\n");
    map_put(&map, 1, 11);
    map_put(&map, 2, 22);
    map_put(&map, 3, 33);
    map_put(&map, 4, 44);
    map_put(&map, 5, 55);
    map_put(&map, 6, 66);
    map_put(&map, 7, 77);
    map_put(&map, 8, 88);
    map_put(&map, 9, 99);
    map_print(&map);

    printf("fourth\n------------\n");
    map_remove(&map, 44);
    map_print(&map);

    printf("fifth\n------------\n");
    map_remove(&map, 22);
    map_remove(&map, 33);
    map_print(&map);

    printf("sixth\n------------\n");
    map_remove(&map, 7);
    map_remove(&map, 8);
    map_remove(&map, 9);
    map_print(&map);

    map_free(&map);
    return 0;
}
