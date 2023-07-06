/*!
  @file gen.h
  @brief The generic module is responsible for generic methods for all the structures

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef GEN_INCLUDED
#define GEN_INCLUDED

#include <string.h>
#include <tc.h>

#include "mem.h"
#include "con.h"
#include "def.h"

#define st_empty(st) ((st).con.size == 0)
#define st_size(st) ((st).con.size)
#define st_capacity(st) ((st).con.capacity)

#define st_new(st_dtype)			\
	(typeof(st_dtype) *) stl_alloc_struct(sizeof(st_dtype))

#define dst_init(st, ...)						\
	do {								\
		(st).con.container =					\
			(typeof((st).con.container[0]) *)		\
			stl_alloc_container(__STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ \
									__VA_OPT__(,) \
									STL_DEFAULT_CONTAINER_CAPACITY)); \
		STL_INIT_CONTAINER((st).con, (st).con.container[0],	\
				   st, __STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ \
								   __VA_OPT__(,) \
								   STL_DEFAULT_CONTAINER_CAPACITY)); \
		memset(&(st), 0, sizeof(st) - sizeof((st).con));	\
	} while (0)

#define st_init(st)							\
	do {								\
		STL_INIT_CONTAINER((st).con, (st).con.container[0], st, \
				   sizeof((st).con.container) / sizeof((st).con.container[0]));	\
		memset(&(st), 0, sizeof(st) - sizeof((st).con));	\
	} while (0)


#define st_free(st)							\
	do {								\
		size_t size;						\
		unsigned char *container;				\
		size = (st).con.size;					\
		container = (st).con.addr;				\
		if (__STL_IS_DYNAMIC_CONTAINER((st).con))		\
			stl_free_container(container, size);		\
		if (((unsigned long) &(st)) < stl_heapaddr)		\
			stl_free_struct((unsigned char *) &(st));	\
	} while (0)

#endif
