#ifndef __VARRAY_H__
#define __VARRAY_H__

typedef struct varray_t {
    int size;
    int count;
    int* items;
} varray_t;

/*
 * Initializes the varray.
 */
varray_t varray_init();

/*
 * Adds an element to the end of the varray.
 */
_Bool varray_add(varray_t* varray, int elm);

/*
 * Adds an element at the specified index, all the sub-sequent elements will be shifted to the right.
 * If index is out of range, it will be appended to the end of the list.
 */
_Bool varray_add_at(varray_t* varray, int index, int elm);

/*
 * Sets the specified element at the specified index in varray.
 * If index is out of range, nothing will be set.
 */
_Bool varray_set(varray_t* varray, int index, int elm);

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
_Bool varray_remove(varray_t* varray, int elm);

/*
 * Removes the element at the specified index from varray.
 * If index is out of range, nothing will be removed.
 */
_Bool varray_remove_at(varray_t* varray, int index);

/*
 * Free the memory block allocated by varray.
 */
void varray_free(varray_t* varray);

#endif // __VARRAY_H__