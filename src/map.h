#ifndef __MAP_H__
#define __MAP_H__

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "generic_map.h"

/*
 * The map consists of const char* key and const char* value.
 */

GENERIC_MAP_HEADER(simple, const char*, const char*, key, value, const char)

#endif // __MAP_H__