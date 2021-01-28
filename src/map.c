#include "map.h"

#define RETURN_OF_VALUE

static bool simple_map_key_equals(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

GENERIC_MAP_SOURCE(simple, const char*, const char*, key, value, const char)
