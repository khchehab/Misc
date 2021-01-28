#ifndef __VARRAY_H__
#define __VARRAY_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "generic_varray.h"

GENERIC_VARRAY_HEADER(int, int, int)

void int_varray_print(int_varray_t* varray);

#endif // __VARRAY_H__