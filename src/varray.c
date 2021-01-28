#include "varray.h"

static const int varray_initial_size = 10;
static const int varray_size_increments = 10;

static bool varray_element_equals(int a, int b);
static void varray_reset(varray_t* varray);
static int varray_index(varray_t* varray, int elm);
static bool varray_grow(varray_t* varray, int new_size);
static bool varray_shrink(varray_t* varray, int new_size);

/*
 * Initializes the varray.
 */
varray_t varray_init() {
    varray_t varray;
    varray_reset(&varray);
    return varray;
}

/*
 * Adds an element to the end of the varray.
 */
bool varray_add(varray_t* varray, int elm) {
    return varray_add_at(varray, -1, elm);
}

/*
 * Adds an element at the specified index, all the sub-sequent elements will be shifted to the right.
 * If index is out of range, it will be appended to the end of the list.
 */
bool varray_add_at(varray_t* varray, int index, int elm) {
    if(varray == NULL || varray->items == NULL) {
        return false;
    }

    if(varray->count >= varray->size) {
        if(!varray_grow(varray, varray->size + varray_size_increments)) {
            return false;
        }
    }

    /* add at a specified index in the list */
    if(index >= 0 && index < varray->count) {
        memmove(varray->items + index + 1, varray->items + index, (varray->count - index) * sizeof(int));
        varray->items[index] = elm;
    } else { /* append to the end of the list */
        varray->items[varray->count] = elm;
    }

    varray->count++;

    return true;
}

/*
 * Sets the specified element at the specified index in varray.
 * If index is out of range, nothing will be set.
 */
bool varray_set(varray_t* varray, int index, int elm) {
    if(varray == NULL || varray->items == NULL || varray->size == 0 || varray->count == 0 || index < 0 || index > varray->count) {
        return false;
    }

    varray->items[index] = elm;
    return true;
}

/*
 * Clear the varray.
 */
void varray_clear(varray_t* varray) {
    varray_free(varray);
    varray_reset(varray);
}

/*
 * Return the value at the specified index from varray.
 */
int* varray_get(varray_t* varray, int index) {
    if(varray == NULL || varray->items == NULL || varray->size == 0 || varray->count == 0 || index < 0 || index > varray->count) {
        return false;
    }

    return &varray->items[index];
}

/*
 * Removes the specified element, if it exists, from varray.
 * If the element exists more than once, onlhy the first occurrence will be removed.
 */
bool varray_remove(varray_t* varray, int elm) {
    int index = varray_index(varray, elm);
    return index < 0 ? false : varray_remove_at(varray, index);
}

/*
 * Removes the element at the specified index from varray.
 * If index is out of range, nothing will be removed.
 */
bool varray_remove_at(varray_t* varray, int index) {
    if(varray == NULL || varray->items == NULL || varray->size == 0 || varray->count == 0 || index < 0 || index > varray->count) {
        return false;
    }

    memmove(varray->items + index, varray->items + index + 1, (varray->count - index - 1) * sizeof(int));
    varray->count--;

    if(varray->count > 0 && varray->count % varray_size_increments == 0) {
        varray_shrink(varray, varray->size - varray_size_increments);
    }

    return true;
}

/*
 * Free the memory block allocated by varray.
 */
void varray_free(varray_t* varray) {
    if(varray == NULL || varray->items == NULL) {
        return;
    }

    free(varray->items);
}

void varray_print(varray_t* varray) {
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

// helper functions
bool varray_element_equals(int a, int b) {
    return a == b;
}

static void varray_reset(varray_t* varray) {
    varray->size = varray_initial_size;
    varray->count = 0;
    varray->items = malloc(varray->size * sizeof(int));
}

int varray_index(varray_t* varray, int elm) {
    if(varray == NULL || varray->items == NULL || varray->count == 0 || varray->size == 0) {
        return -1;
    }

    for(int i = 0; i < varray->count; i++) {
        if(varray_element_equals(varray->items[i], elm)) {
            return i;
        }
    }

    return -1;
}

bool varray_grow(varray_t* varray, int new_size) {
    int* tmp = realloc(varray->items, new_size * sizeof(int));
    if(tmp == NULL) {
        /* could not grow the list, so can't add the element */
        return false;
    }

    varray->size = new_size;
    varray->items = tmp;
    return true;
}

bool varray_shrink(varray_t* varray, int new_size) {
    int* tmp = realloc(varray->items, new_size * sizeof(int));
    
    /* if list could not be shrunk, it will still be okay since there will be more space anyway */
    if(tmp != NULL) {
        varray->size = new_size;
        varray->items = tmp;
    }

    return true;
}
