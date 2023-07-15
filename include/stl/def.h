


#ifndef DEF_INCLUDED
#define DEF_INCLUDED

#include <stddef.h>

#define __STL_FIRST(a, ...) a
#define __STL_SECOND(a, b, ...) b
#define ptr(dtype) 1, dtype

extern int stl_memcmp(unsigned char *item1, unsigned char *item2, size_t item_size);

#endif

