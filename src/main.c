#include <stdio.h>
#include "simple_map.h"

int main(int argc, char* argv[]) {
    map_t* map = map_init();

    printf("first\n");
    map_put(map, 42, "Hello World!");
    map_put(map, 33, "Nothing much");
    map_put(map, 22, "Boredom!!!!!");
    map_print(map);

    printf("first.1\n");
    map_put(map, 1, "one");
    map_put(map, 2, "two");
    map_put(map, 3, "three");
    map_put(map, 4, "four");
    map_put(map, 5, "five");
    map_put(map, 6, "six");
    map_put(map, 7, "seven");
    map_put(map, 8, "eight");
    map_put(map, 9, "nine");
    map_print(map);

    printf("second\n");
    map_remove(map, 44);
    map_print(map);

    printf("third\n");
    map_remove(map, 33);
    map_remove(map, 42);
    map_print(map);

    printf("fourth\n");
    map_remove(map, 22);
    map_print(map);

    map_free(map);
    return 0;
}
