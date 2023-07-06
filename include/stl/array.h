/*!
  @file array.h
  @brief This library provides a array data structure

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/


#ifndef ARRAY_INCLUDED
#define ARRAY_INCLUDED

#include "con.h"
#include "mem.h"
#include "def.h"

#define STL_DEFAULT_ARRAY_CAPACITY STL_DEFAULT_CONTAINER_CAPACITY
#define STL_DEFAULT_DARRAY_CAPACITY STL_DEFAULT_DCONTAINER_CAPACITY
#define STL_DEFAULT_DARRAY_INCREASE_RATE STL_DEFAULT_DCONTAINER_INCREASE_RATE

typedef struct {
	size_t size;
	void *container;
	__stl_con_t con;
} __stl_array_t;

#define __stl_def_ptr_array(one, dtype, ...)				\
	typedef struct {						\
		size_t size;						\
		STL_CONTAINER(1, dtype, STL_DEFAULT_ARRAY_CAPACITY	\
			      __VA_OPT__(,) __VA_ARGS__) con;		\
	} __stl_array_t_ptr ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define __stl_def_array(dtype, ...)					\
	typedef struct {						\
		size_t size;						\
		STL_CONTAINER(0, dtype, STL_DEFAULT_ARRAY_CAPACITY	\
			      __VA_OPT__(,) __VA_ARGS__) con;		\
	} __stl_array_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__


#define def_array(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_def_ptr_array(dtype __VA_OPT__(,) __VA_ARGS__))	\
	     (__stl_def_array(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_def_ptr_darray(one, dtype, ...)				\
	typedef struct {						\
		size_t size;						\
		STL_DCONTAINER(1, dtype) con;				\
	} __stl_darray_t_ptr_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define __stl_def_darray(dtype, ...)					\
	typedef struct {						\
		size_t size;						\
		STL_DCONTAINER(0, dtype) con;				\
	} __stl_darray_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define def_darray(dtype)				\
	STL_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_def_ptr_darray(dtype))		\
	     (__stl_def_darray(dtype))

#define __stl_array_ptr(one, dtype, ...)				\
	__stl_array_t_ptr_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define __stl_array(dtype, ...)					\
	__stl_array_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define array(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_array_ptr(dtype __VA_OPT__(,) __VA_ARGS__))		\
	     (__stl_array(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_darray_ptr(one, dtype, ...)				\
	__stl_darray_t_ptr_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__
#define __stl_darray(dtype, ...)					\
	__stl_darray_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define darray(dtype)					\
	STL_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_darray_ptr(dtype))			\
	     (__stl_darray(dtype))

#define new_darray(dtype, ...)					\
	STL_IF_ELSE_PTR_DTYPE(dtype)				\
	     ((__stl_darray_ptr(dtype) *))			\
	     ((__stl_darray(dtype) *))				\
	     stl_alloc_struct(STL_IF_ELSE_PTR_DTYPE(dtype)	\
			      (sizeof(__stl_darray_ptr(dtype)))	\
			      (sizeof(__stl_darray(dtype))),		\
			      STL_IF_ELSE_PTR_DTYPE(dtype)(sizeof(__STL_SECOND(dtype) *))(sizeof(dtype)) \
			      * __STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) \
							    STL_DEFAULT_DARRAY_CAPACITY))

#define array_init(array, ...)						\
	do {								\
		(array).size = 0;					\
		STL_INIT_D_CONTAINER_DTYPE_SIZE((array).con, (array).con.container[0]); \
		STL_INIT_D_CONTAINER_ST_SIZE((array).con, (array));	\
		STL_INIT_D_CONTAINER_CAPACITY((array).con);		\
	} while (0)

#define array_size(array) (array).size
#define array_empty(array) ((array).size == 0)
#define array_append(array, item)		\
	(array).con.container[__stl_array_insert_byindex((__stl_array_t *) &(array), (array).size)] = item

extern size_t __stl_array_insert_byindex(__stl_array_t *array, size_t ind);

#endif

