#include <stdlib.h>
#include <stdbool.h>
#include "varray.h"

#define INITIAL_SIZE 10
#define SIZE_INCREMENTS 10

static bool varray_grow(varray_t* varray, int new_size);
static bool varray_shrink(varray_t* varray, int new_size);

/*
 * Initializes the varray.
 */
varray_t varray_init() {
    varray_t varray;
    varray.size = INITIAL_SIZE;
    varray.count = 0;
    varray.items = malloc(varray.size * sizeof(int));
    return varray;
}

/*
 * Adds an element to the end of the varray.
 */
bool varray_add(varray_t* varray, int elm);

/*
 * Adds an element at the specified index, all the sub-sequent elements will be shifted to the right.
 * If index is out of range, it will be appended to the end of the list.
 */
bool varray_add_at(varray_t* varray, int index, int elm) {
    if(varray == NULL) {
        return false;
    }

    if(varray->count >= varray->size) {
        if(!varray_grow(varray, varray->size + SIZE_INCREMENTS)) {
            return false;
        }
    }

    if(index == -1) {
        *(varray->items + varray->count) = elm;
    } else {
        memmove(varray->items + index + 1, varray->items + index, (varray->count - index) * sizeof(int));
        *(varray->items + index) = elm;
    }

    varray->count++;
    return true;
}

/*
 * Sets the specified element at the specified index in varray.
 * If index is out of range, nothing will be set.
 */
bool varray_set(varray_t* varray, int index, int elm);

/*
 * Clear the varray.
 */
void varray_clear(varray_t* varray);

/*
 * Return the value at the specified index from varray.
 */
int varray_get(varray_t* varray, int index);

/*
 * Removes the specified element, if it exists, from varray.
 */
bool varray_remove(varray_t* varray, int elm);

/*
 * Removes the element at the specified index from varray.
 * If index is out of range, nothing will be removed.
 */
bool varray_remove_at(varray_t* varray, int index);

/*
 * Free the memory block allocated by varray.
 */
void varray_free(varray_t* varray) {
    if(varray == NULL || varray->items == NULL) {
        return;
    }

    free(varray->items);
}

// helper functions
bool varray_grow(varray_t* varray, int new_size) {
    int* tmp = realloc(varray->items, new_size * sizeof(int));
    if(tmp == NULL) {
        // could not grow the list, so can't add element
        return false;
    }

    varray->size = new_size;
    varray->items = tmp;
    return true;
}

bool varray_shrink(varray_t* varray, int new_size) {
    int* tmp = realloc(varray->items, new_size * sizeof(int));
    
    // if list could not be shrunk, it will still be okay since there will be more space anyway
    if(tmp != NULL) {
        varray->size = new_size;
        varray->items = tmp;
    }

    return true;
}
