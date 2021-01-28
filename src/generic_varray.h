#ifndef __GENERIC_VARRAY_H__
#define __GENERIC_VARRAY_H__

/*
 * Below are macros to define the header and source of a map by supplying the below information:
 * 1. prefix: the prefix for the varray, it will be <prefix>_varray_t.
 * 2. item_type: the type of the list (eg. int).
 * 3. get_item_type: the type for the get function. This get function should return a pointer,
 *    so if item_type is a pointer in it of itself, here it should be supplied without asterisk
 *    since it will be added automatically.
 * 
 * Pre-Requisite:
 * 1. Before calling the source macro in the source file, a function that compares items must exist
 *    with the following prototype:
 *    static bool <prefix>_varray_element_equals(item_type a, item_type b);
 * 
 *    Without this function, it will not work. So it must be defined prior to calling GENERIC_VARRAY_SOURCE.
 *    THIS IS VERY IMPORTANT!!!
 *
 * 2. Include all the needed headers (especially structs are used as item type).
 * 3. This is kind of a weird one, but if the item type is a pointer to something, the get function
 *    must return the element as it is (and not the address of it), otherwise if item type is not a pointer,
 *    since the function returns a pointer, we need to return the address of the element.
 *    For this, we use the macro RETURN_OF_VALUE, which must be defined in the source file as either empty
 *    for pointer item types and `&` for non-pointer item types.
 */

#define GENERIC_VARRAY_HEADER(prefix, item_type, get_item_type)                                           \
    typedef struct prefix ## _varray_t {                                                                  \
        int size;                                                                                         \
        int count;                                                                                        \
        item_type* items;                                                                                 \
    } prefix ## _varray_t;                                                                                \
                                                                                                          \
    /*
     * Initializes the varray.
     */                                                                                                   \
    prefix ## _varray_t prefix ## _varray_init();                                                         \
                                                                                                          \
    /*
     * Adds an element to the end of the varray.
     */                                                                                                   \
    bool prefix ## _varray_add(prefix ## _varray_t* varray, item_type elm);                               \
                                                                                                          \
    /*
     * Adds an element at the specified index, all the sub-sequent elements will be shifted to the right.
     * If index is out of range, it will be appended to the end of the list.
     */                                                                                                   \
    bool prefix ## _varray_add_at(prefix ## _varray_t* varray, int index, item_type elm);                 \
                                                                                                          \
    /*
     * Sets the specified element at the specified index in varray.
     * If index is out of range, nothing will be set.
     */                                                                                                   \
    bool prefix ## _varray_set(prefix ## _varray_t* varray, int index, item_type elm);                    \
                                                                                                          \
    /*
     * Clear the varray.
     */                                                                                                   \
    void prefix ## _varray_clear(prefix ## _varray_t* varray);                                            \
                                                                                                          \
    /*
     * Return the value at the specified index from varray.
     */                                                                                                   \
    get_item_type* prefix ## _varray_get(prefix ## _varray_t* varray, int index);                         \
                                                                                                          \
    /*
     * Removes the specified element, if it exists, from varray.
     */                                                                                                   \
    bool prefix ## _varray_remove(prefix ## _varray_t* varray, item_type elm);                            \
                                                                                                          \
    /*
     * Removes the element at the specified index from varray.
     * If index is out of range, nothing will be removed.
     */                                                                                                   \
    bool prefix ## _varray_remove_at(prefix ## _varray_t* varray, int index);                             \
                                                                                                          \
    /*
     * Free the memory block allocated by varray.
     */                                                                                                   \
    void prefix ## _varray_free(prefix ## _varray_t* varray);                                             \

#define GENERIC_VARRAY_SOURCE(prefix, item_type, get_item_type)                                                                        \
    static const int prefix ## _varray_initial_size = 10;                                                                              \
    static const int prefix ## _varray_size_increments = 10;                                                                           \
                                                                                                                                       \
    static void prefix ## _varray_reset(prefix ## _varray_t* varray);                                                                  \
    static int prefix ## _varray_index(prefix ## _varray_t* varray, item_type elm);                                                    \
    static bool prefix ## _varray_grow(prefix ## _varray_t* varray, int new_size);                                                     \
    static bool prefix ## _varray_shrink(prefix ## _varray_t* varray, int new_size);                                                   \
                                                                                                                                       \
    /*
     * Initializes the varray.
     */                                                                                                                                \
    prefix ## _varray_t prefix ## _varray_init() {                                                                                     \
        prefix ## _varray_t varray;                                                                                                    \
        prefix ## _varray_reset(&varray);                                                                                              \
        return varray;                                                                                                                 \
    }                                                                                                                                  \
                                                                                                                                       \
    /*
     * Adds an element to the end of the varray.
     */                                                                                                                                \
    bool prefix ## _varray_add(prefix ## _varray_t* varray, item_type elm) {                                                           \
        return prefix ## _varray_add_at(varray, -1, elm);                                                                              \
    }                                                                                                                                  \
                                                                                                                                       \
    /*
     * Adds an element at the specified index, all the sub-sequent elements will be shifted to the right.
     * If index is out of range, it will be appended to the end of the list.
     */                                                                                                                                \
    bool prefix ## _varray_add_at(prefix ## _varray_t* varray, int index, item_type elm) {                                             \
        if(varray == NULL || varray->items == NULL) {                                                                                  \
            return false;                                                                                                              \
        }                                                                                                                              \
                                                                                                                                       \
        if(varray->count >= varray->size) {                                                                                            \
            if(!prefix ## _varray_grow(varray, varray->size + prefix ## _varray_size_increments)) {                                    \
                return false;                                                                                                          \
            }                                                                                                                          \
        }                                                                                                                              \
                                                                                                                                       \
        /* add at a specified index in the list */                                                                                     \
        if(index >= 0 && index < varray->count) {                                                                                      \
            memmove(varray->items + index + 1, varray->items + index, (varray->count - index) * sizeof(item_type));                    \
            varray->items[index] = elm;                                                                                                \
        } else { /* append to the end of the list */                                                                                   \
            varray->items[varray->count] = elm;                                                                                        \
        }                                                                                                                              \
                                                                                                                                       \
        varray->count++;                                                                                                               \
                                                                                                                                       \
        return true;                                                                                                                   \
    }                                                                                                                                  \
                                                                                                                                       \
    /*
     * Sets the specified element at the specified index in varray.
     * If index is out of range, nothing will be set.
     */                                                                                                                                \
    bool prefix ## _varray_set(prefix ## _varray_t* varray, int index, item_type elm) {                                                \
        if(varray == NULL || varray->items == NULL || varray->size == 0 || varray->count == 0 || index < 0 || index > varray->count) { \
            return false;                                                                                                              \
        }                                                                                                                              \
                                                                                                                                       \
        varray->items[index] = elm;                                                                                                    \
        return true;                                                                                                                   \
    }                                                                                                                                  \
                                                                                                                                       \
    /*
     * Clear the varray.
     */                                                                                                                                \
    void prefix ## _varray_clear(prefix ## _varray_t* varray) {                                                                        \
        prefix ## _varray_free(varray);                                                                                                \
        prefix ## _varray_reset(varray);                                                                                               \
    }                                                                                                                                  \
                                                                                                                                       \
    /*
     * Return the value at the specified index from varray.
     */                                                                                                                                \
    get_item_type* prefix ## _varray_get(prefix ## _varray_t* varray, int index) {                                                     \
        if(varray == NULL || varray->items == NULL || varray->size == 0 || varray->count == 0 || index < 0 || index > varray->count) { \
            return NULL;                                                                                                               \
        }                                                                                                                              \
                                                                                                                                       \
        return RETURN_OF_VALUE varray->items[index];                                                                                   \
    }                                                                                                                                  \
                                                                                                                                       \
    /*
     * Removes the specified element, if it exists, from varray.
     * If the element exists more than once, onlhy the first occurrence will be removed.
     */                                                                                                                                \
    bool prefix ## _varray_remove(prefix ## _varray_t* varray, item_type elm) {                                                        \
        int index = prefix ## _varray_index(varray, elm);                                                                              \
        return index < 0 ? false : prefix ## _varray_remove_at(varray, index);                                                         \
    }                                                                                                                                  \
                                                                                                                                       \
    /*
     * Removes the element at the specified index from varray.
     * If index is out of range, nothing will be removed.
     */                                                                                                                                \
    bool prefix ## _varray_remove_at(prefix ## _varray_t* varray, int index) {                                                         \
        if(varray == NULL || varray->items == NULL || varray->size == 0 || varray->count == 0 || index < 0 || index > varray->count) { \
            return false;                                                                                                              \
        }                                                                                                                              \
                                                                                                                                       \
        memmove(varray->items + index, varray->items + index + 1, (varray->count - index - 1) * sizeof(item_type));                    \
        varray->count--;                                                                                                               \
                                                                                                                                       \
        if(varray->count > 0 && varray->count % prefix ## _varray_size_increments == 0) {                                              \
            prefix ## _varray_shrink(varray, varray->size - prefix ## _varray_size_increments);                                        \
        }                                                                                                                              \
                                                                                                                                       \
        return true;                                                                                                                   \
    }                                                                                                                                  \
                                                                                                                                       \
    /*
     * Free the memory block allocated by varray.
     */                                                                                                                                \
    void prefix ## _varray_free(prefix ## _varray_t* varray) {                                                                         \
        if(varray == NULL || varray->items == NULL) {                                                                                  \
            return;                                                                                                                    \
        }                                                                                                                              \
                                                                                                                                       \
        free(varray->items);                                                                                                           \
    }                                                                                                                                  \
                                                                                                                                       \
    /* helper functions */                                                                                                             \
                                                                                                                                       \
    static void prefix ## _varray_reset(prefix ## _varray_t* varray) {                                                                 \
        varray->size = prefix ## _varray_initial_size;                                                                                 \
        varray->count = 0;                                                                                                             \
        varray->items = malloc(varray->size * sizeof(item_type));                                                                      \
    }                                                                                                                                  \
                                                                                                                                       \
    int prefix ## _varray_index(prefix ## _varray_t* varray, item_type elm) {                                                          \
        if(varray == NULL || varray->items == NULL || varray->count == 0 || varray->size == 0) {                                       \
            return -1;                                                                                                                 \
        }                                                                                                                              \
                                                                                                                                       \
        for(int i = 0; i < varray->count; i++) {                                                                                       \
            if(prefix ## _varray_element_equals(varray->items[i], elm)) {                                                              \
                return i;                                                                                                              \
            }                                                                                                                          \
        }                                                                                                                              \
                                                                                                                                       \
        return -1;                                                                                                                     \
    }                                                                                                                                  \
                                                                                                                                       \
    bool prefix ## _varray_grow(prefix ## _varray_t* varray, int new_size) {                                                           \
        int* tmp = realloc(varray->items, new_size * sizeof(item_type));                                                               \
        if(tmp == NULL) {                                                                                                              \
            /* could not grow the list, so can't add the element */                                                                    \
            return false;                                                                                                              \
        }                                                                                                                              \
                                                                                                                                       \
        varray->size = new_size;                                                                                                       \
        varray->items = tmp;                                                                                                           \
        return true;                                                                                                                   \
    }                                                                                                                                  \
                                                                                                                                       \
    bool prefix ## _varray_shrink(prefix ## _varray_t* varray, int new_size) {                                                         \
        int* tmp = realloc(varray->items, new_size * sizeof(item_type));                                                               \
                                                                                                                                       \
        /* if list could not be shrunk, it will still be okay since there will be more space anyway */                                 \
        if(tmp != NULL) {                                                                                                              \
            varray->size = new_size;                                                                                                   \
            varray->items = tmp;                                                                                                       \
        }                                                                                                                              \
                                                                                                                                       \
        return true;                                                                                                                   \
    }                                                                                                                                  \

#endif // __GENERIC_VARRAY_H__