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

#define STL_DEFAULT_CONTAINER_CAPACITY 1024
#define STL_DEFAULT_DCONTAINER_CAPACITY 1024
#define STL_DEFAULT_DCONTAINER_INCREASE_RATE 2

extern unsigned long stl_heapaddr;

typedef struct {	
	size_t capacity, dtype_size, st_size;
	unsigned char *container;
} __stl_con_t;

#define __STL_CONTAINER_SELECT_SIZE(X, ...) X
#define __STL_IS_DYNAMIC_CONTAINER(X) (((unsigned long) X) < stl_heapaddr)
#define STL_CONTAINER(cond, dtype, dcapacity, ...)			\
	struct  {							\
		size_t capacity, dtype_size, st_size;				\
		__STL_IF_ELSE(cond)					\
		     (dtype *container[__STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) dcapacity)]) \
		     (dtype container[__STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) dcapacity)]); \
	}

#define STL_DCONTAINER(cond, dtype)					\
	struct  {							\
		size_t capacity, dtype_size, st_size;			\
		__STL_IF_ELSE(cond)					\
		     (dtype **container)				\
		     (dtype *container);				\
	}

#define STL_INIT_D_CONTAINER_DTYPE_SIZE(con, dtype)	\
	con.dtype_size = sizeof(dtype)

#define STL_INIT_D_CONTAINER_ST_SIZE(con, st)				\
	con.st_size = sizeof(st)					\
		
#define STL_INIT_D_CONTAINER_CAPACITY(con)				\
	con.capacity = stl_init_con_capacity((unsigned char *) con.container, \
					     sizeof(con.container),	\
					     con.dtype_size)

#define STL_CONTAINER_CAPACITY(con)		\
	con.capacity

extern size_t stl_init_con_capacity(unsigned char *container, size_t static_container_size, size_t dtype_size);

#endif
