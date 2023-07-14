/*!
  @file con.h
  @brief The container module is responsible for managing memory allocation for a collection of
  data structures. This includes allocating static memory for fixed-size data structures and
  dynamic memory for variable-size data structures.

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef STL_CON_INCLUDED
#define STL_CON_INCLUDED

#include <stddef.h>
#include "def.h"
#include "mem.h"

#define STL_DEFAULT_CONTAINER_CAPACITY 1024
#define STL_DEFAULT_DCONTAINER_CAPACITY 1024
#define STL_DEFAULT_DCONTAINER_INCREASE_RATE 2


extern unsigned long stl_heapaddr;

typedef enum {
	STL_STATIC = 0,
	STL_DYNAMIC
} CONTAINER_TYPE;

typedef struct {	
	size_t capacity, dtype_size, st_size, size;
	CONTAINER_TYPE type;
	unsigned char *addr, *container;
} __stl_con_t;

#define STL_CONTAINER_SIZE sizeof(__stl_con_t)

#define __STL_CONTAINER_SELECT_CAPACITY(X, ...) (X)

#define STL_IS_DYNAMIC_CONTAINER(con) (STL_CONTAINER_SIZE == sizeof(con))

#define STL_CONTAINER(cond, dtype, def_capacity, ...)			\
	struct  {							\
		size_t capacity, dtype_size, st_size, size;		\
		CONTAINER_TYPE type;					\
		unsigned char *addr;					\
		__STL_IF_ELSE(cond)					\
		     (dtype *container[__STL_CONTAINER_SELECT_CAPACITY(__VA_ARGS__ \
								       __VA_OPT__(,) def_capacity)]) \
		     (dtype container[__STL_CONTAINER_SELECT_CAPACITY(__VA_ARGS__ \
								      __VA_OPT__(,) def_capacity)]); \
	}

#define STL_DCONTAINER(cond, dtype)					\
	struct  {							\
		size_t capacity, dtype_size, st_size, size;		\
		CONTAINER_TYPE type;					\
		unsigned char *addr;					\
		__STL_IF_ELSE(cond)					\
		     (dtype **container)				\
		     (dtype *container);				\
	}

#define STL_INIT_CONTAINER(con, dtype, st, c)				\
	do {								\
		(con).size = 0;						\
		(con).dtype_size = sizeof(dtype);			\
		(con).st_size = sizeof(st);				\
		(con).addr = (unsigned char *) (con).container;		\
		(con).type = STL_STATIC;				\
 		(con).capacity = c;					\
	} while (0)


#define STL_INIT_DCONTAINER(con, dtype, st, c)			\
	do {								\
		(con).container =					\
			(dtype *)					\
			stl_alloc_container(c * sizeof(dtype));		\
		(con).size = 0;						\
		(con).dtype_size = sizeof(dtype);			\
		(con).st_size = sizeof(st);				\
		(con).addr = (unsigned char *) (con).container;		\
		(con).type = STL_DYNAMIC;				\
 		(con).capacity = c;					\
	} while (0)

#define STL_CONTAINER_CAPACITY(con)		\
	(con).capacity

#endif
