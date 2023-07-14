/*!
  @file gen.h
  @brief The generic module is responsible for generic methods for all the structures

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef GEN_INCLUDED
#define GEN_INCLUDED

#include "mem.h"
#include "con.h"
#include "def.h"
#include "init.h"

#define st_empty(st) ((st).con.size == 0)
#define st_size(st) ((st).con.size)
#define st_capacity(st) ((st).con.capacity)

#define new_st(st_dtype)					\
	(typeof(st_dtype) *) stl_alloc_struct(sizeof(st_dtype))

#define init_dst(st, ...)						\
	do {								\
		STL_INIT_DCONTAINER((st).con, typeof((st).con.container[0]), \
				    st, __STL_CONTAINER_SELECT_CAPACITY(__VA_ARGS__ \
									__VA_OPT__(,) \
									STL_DEFAULT_CONTAINER_CAPACITY)); \
		__stl_initialize_st(st);				\
	} while (0)

#define init_st(st)							\
	do {								\
		STL_INIT_CONTAINER((st).con, typeof((st).con.container[0]), st, \
				   sizeof((st).con.container) / sizeof((st).con.container[0]));	\
		__stl_initialize_st(st);				\
	} while (0)

#define stl_free(st)							\
	do {								\
		if (STL_IS_DYNAMIC_CONTAINER((st).con))			\
			stl_free_container((st).con.addr, (st).con.capacity); \
		if (((unsigned long) &(st)) < stl_heapaddr)		\
			stl_free_struct((unsigned char *) &(st));	\
		__stl_destroy_st(st);					\
	} while (0)

#endif
