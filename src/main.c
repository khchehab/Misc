#include <stdio.h>
#include "varray.h"

int main(int argc, char* argv[]) {
    varray_t varray = varray_init();

    printf("--------------\nfirst\n");
    varray_print(&varray);
    
    printf("--------------\nsecond\n");
    varray_add(&varray, 42);
    varray_add(&varray, 43);
    varray_add(&varray, 22);
    varray_print(&varray);
    
    printf("--------------\nthird\n");
    for(int i = 0; i < 10; i++) {
        varray_add(&varray, i + 1);
    }
    varray_print(&varray);
    varray_add_at(&varray, 1, 23);
    varray_add_at(&varray, 5, 65);
    varray_print(&varray);
    
    printf("--------------\nfourth\n");
    varray_clear(&varray);
    varray_print(&varray);

    varray_add(&varray, 42);
    varray_add(&varray, 43);
    varray_add(&varray, 22);
    for(int i = 0; i < 10; i++) {
        varray_add(&varray, i + 1);
    }
    varray_add_at(&varray, 1, 23);
    varray_add_at(&varray, 5, 65);
    
    printf("--------------\nfifth\n");
    varray_remove(&varray, 44);
    varray_remove(&varray, 22);
    varray_remove(&varray, 99);
    varray_remove(&varray, 11002);
    varray_print(&varray);
    
    printf("--------------\nsixth\n");
    varray_remove_at(&varray, 2);
    varray_remove_at(&varray, 0);
    varray_remove_at(&varray, 101);
    varray_print(&varray);
    
    printf("--------------\nseventh\n");
    int* val;
    if((val = varray_get(&varray, 0)) == NULL) {
        printf("Index 0 doesn't have any element\n");
    } else {
        printf("Index 0 has a value of %d\n", *val);
    }
    if((val = varray_get(&varray, 5)) == NULL) {
        printf("Index 5 doesn't have any element\n");
    } else {
        printf("Index 5 has a value of %d\n", *val);
    }
    if((val = varray_get(&varray, 565)) == NULL) {
        printf("Index 565 doesn't have any element\n");
    } else {
        printf("Index 565 has a value of %d\n", *val);
    }
    varray_print(&varray);
    
    printf("--------------\neighth\n");
    varray_remove(&varray, 8);
    varray_remove(&varray, 7);
    varray_remove(&varray, 6);
    varray_remove(&varray, 5);
    varray_print(&varray);

    varray_free(&varray);
    return 0;
}
