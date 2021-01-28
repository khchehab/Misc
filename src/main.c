#include <stdio.h>
#include "varray.h"

int main(int argc, char* argv[]) {
    int_varray_t varray = int_varray_init();

    printf("--------------\nfirst\n");
    int_varray_print(&varray);
    
    printf("--------------\nsecond\n");
    int_varray_add(&varray, 42);
    int_varray_add(&varray, 43);
    int_varray_add(&varray, 22);
    int_varray_print(&varray);
    
    printf("--------------\nthird\n");
    for(int i = 0; i < 10; i++) {
        int_varray_add(&varray, i + 1);
    }
    int_varray_print(&varray);
    int_varray_add_at(&varray, 1, 23);
    int_varray_add_at(&varray, 5, 65);
    int_varray_print(&varray);
    
    printf("--------------\nfourth\n");
    int_varray_clear(&varray);
    int_varray_print(&varray);

    int_varray_add(&varray, 42);
    int_varray_add(&varray, 43);
    int_varray_add(&varray, 22);
    for(int i = 0; i < 10; i++) {
        int_varray_add(&varray, i + 1);
    }
    int_varray_add_at(&varray, 1, 23);
    int_varray_add_at(&varray, 5, 65);
    
    printf("--------------\nfifth\n");
    int_varray_remove(&varray, 44);
    int_varray_remove(&varray, 22);
    int_varray_remove(&varray, 99);
    int_varray_remove(&varray, 11002);
    int_varray_print(&varray);
    
    printf("--------------\nsixth\n");
    int_varray_remove_at(&varray, 2);
    int_varray_remove_at(&varray, 0);
    int_varray_remove_at(&varray, 101);
    int_varray_print(&varray);
    
    printf("--------------\nseventh\n");
    int* val;
    if((val = int_varray_get(&varray, 0)) == NULL) {
        printf("Index 0 doesn't have any element\n");
    } else {
        printf("Index 0 has a value of %d\n", *val);
    }
    if((val = int_varray_get(&varray, 5)) == NULL) {
        printf("Index 5 doesn't have any element\n");
    } else {
        printf("Index 5 has a value of %d\n", *val);
    }
    if((val = int_varray_get(&varray, 565)) == NULL) {
        printf("Index 565 doesn't have any element\n");
    } else {
        printf("Index 565 has a value of %d\n", *val);
    }
    int_varray_print(&varray);
    
    printf("--------------\neighth\n");
    int_varray_remove(&varray, 8);
    int_varray_remove(&varray, 7);
    int_varray_remove(&varray, 6);
    int_varray_remove(&varray, 5);
    int_varray_print(&varray);

    int_varray_free(&varray);
    return 0;
}
