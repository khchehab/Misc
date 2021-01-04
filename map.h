#ifndef __MAP_H__
#define __MAP_H__

/*
 * Map for integer key/value pairs.
 */

typedef struct entry {
    int key;
    int value;
} entry;

typedef struct map {
    entry* entries;
    int size;
    int count;
} map;

// todo:
// 1. maybe have a parameter to decide if the map is fixed size or can expand to accommodate more entires than original specified size.
// 2. see how to handle errors, like an error message. Maybe do something similar to SDL, like SDL_GetError or something.
// 3. maybe add ordering.
// 4. see if there ar eany performance issues with the current oeprations. for example when looking for existance of a key, if it is slow for big number of entries.
// 5. add unit testing for the map (use Unity testing framework)

/*
 * Initializes a map of integer key/value pairs with the specified size.
 */
map* init_map(int size);

/*
 * Free the map from memory.
 * This must be called at the end if a map is initialized.
 */
void free_map(map* map);

/*
 * Inserts a pair to the specified map.
 * It will return true if inserted, and false otherwise.
 */
_Bool insert_entry(map* map, int key, int value);

/*
 * Removes a pair from the speicified map by its key.
 * It will return true if removed, and false otherwise.
 */
_Bool remove_entry(map* map, int key);

/*
 * Get the value of the specified key from the map.
 */
int get(map* map, int key);

/*
 * Prints the map to the console.
 */
void print_map(map* map);

/*
 * Returns an error text if the last operation failed for some reason.
 * If another operation was done, previous operation's error text will not persist.
 */
char* map_error();

#endif // __MAP_H__
