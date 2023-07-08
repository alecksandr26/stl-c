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
#define STL_DEFAULT_DARRAY_INCREASE_RATE STL_DEFAULT_DCONTAINER_INCREASE_RATE

typedef struct {
	__stl_con_t con;
} __stl_array_t;

#define __stl_def_ptr_array(one, dtype, ...)				\
	typedef struct {						\
		STL_CONTAINER(1, dtype, STL_DEFAULT_ARRAY_CAPACITY	\
			      __VA_OPT__(,) __VA_ARGS__) con;		\
	} __stl_array_t_ptr ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define __stl_def_array(dtype, ...)					\
	typedef struct {						\
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

#define array_append(array, item)					\
	*((typeof((array).con.container[0]) *)				\
	  __stl_array_insert_byindex((__stl_array_t *) &(array), st_size(array))) = item

#define array_at(array, index)						\
	(array).con.container[__stl_array_at((__stl_array_t *) &(array), index)]

#define array_ins(array, index, item)					\
	*((typeof((array).con.container[0]) *)				\
	  __stl_array_insert_byindex((__stl_array_t *) &(array), index)) = item

#define array_rem(array, index)			\
	__stl_array_insert_rem((__stl_array_t *) &(array), index)

#define array_pop(array)			\
	*((typeof((array).con.container[0]) *)  __stl_array_pop((__stl_array_t *) &(array)))

#define array_front(array)			\
	array.con.container[0]

#define array_back(array)			\
	array.con.container[st_size(array) - 1]

extern unsigned char *__stl_array_insert_byindex(__stl_array_t *array, size_t ind);
extern unsigned char *__stl_array_pop(__stl_array_t *array);
extern void __stl_array_insert_rem(__stl_array_t *array, size_t ind);
extern size_t __stl_array_at(__stl_array_t *array, size_t index);

#endif

