#include "varray.h"

static bool int_varray_element_equals(int a, int b) {
    return a == b;
}

#define RETURN_OF_VALUE &

GENERIC_VARRAY_SOURCE(int, int, int)

void int_varray_print(int_varray_t* varray) {
    if(varray == NULL || varray->items == NULL) {
        printf("Varray is null!!!\n");
        return;
    }

    if(varray->size == 0 || varray->count == 0) {
        printf("Varray is empty!\n");
        return;
    }

    printf("Varray has size of %d and count of %d\n", varray->size, varray->count);
    printf("[");

    for(int i = 0; i < varray->count; i++) {
        if(i > 0) {
            printf(", ");
        }

        printf("%d", varray->items[i]);
    }

    printf("]\n\n");
}
