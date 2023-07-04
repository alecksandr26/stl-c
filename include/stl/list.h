/*!
  @file list.h
  @brief This library provides a list data structure implementation, combining an array with a simple
  linked list.

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef LIST_INCLUDED
#define LIST_INCLUDED

#include "con.h"
#include "mem.h"
#include "def.h"

#include "stack.h"

#define STL_DEFAULT_LIST_CAPACITY STL_DEFAULT_CONTAINER_CAPACITY
#define STL_DEFAULT_DLIST_CAPACITY STL_DEFAULT_DCONTAINER_CAPACITY
#define STL_DEFAULT_DLIST_INCREASE_RATE STL_DEFAULT_DCONTAINER_INCREASE_RATE

typedef struct __stl_unorderedlist_t {
	int lind;
	size_t pind;
} __stl_unorderedlist_t;

typedef struct __stl_linkedlist_t {
	struct __stl_linkedlist_t *next, *prev;
} __stl_linkedlist_t;

def_stack(size_t);
def_dstack(size_t);

typedef struct {
	size_t size, size_ul, size_con;
	stack(size_t) *st;
	__stl_unorderedlist_t *uelems;
	__stl_linkedlist_t *linked;
	void *container;
	__stl_con_t con;
} __stl_list_t;

#define __stl_def_ptr_list(one, dtype, ...)				\
	typedef struct {						\
		size_t size, size_ul, size_con;				\
		stack(size_t) *st;					\
		__stl_unorderedlist_t *uelems;				\
		__stl_linkedlist_t *linked;				\
		dtype *container;					\
		STL_CONTAINER(1, dtype, STL_DEFAULT_LIST_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
		__stl_unorderedlist_t __ulist_alloc[__STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) \
										STL_DEFAULT_LIST_CAPACITY)]; \
		__stl_linkedlist_t __linked_alloc[__STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) \
									      STL_DEFAULT_LIST_CAPACITY)]; \
		stack(size_t) __st_alloc;				\
	} __stl_list_t_ptr_ ## dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define __stl_def_list(dtype, ...)					\
	typedef struct {						\
		size_t size, size_ul, size_con;				\
		stack(size_t) *st;					\
		__stl_unorderedlist_t *uelems;				\
		__stl_linkedlist_t *linked;				\
		dtype *container;					\
		STL_CONTAINER(0, dtype, STL_DEFAULT_LIST_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
		__stl_unorderedlist_t __ulist_alloc[__STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) \
								      STL_DEFAULT_LIST_CAPACITY)]; \
		__stl_linkedlist_t __linked_alloc[__STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) \
									 STL_DEFAULT_LIST_CAPACITY)]; \
		stack(size_t) __st_alloc;					\
	} __stl_list_t_ ## dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define def_list(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_def_ptr_list(dtype __VA_OPT__(,) __VA_ARGS__))	\
	     (__stl_def_list(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_def_ptr_dlist(one, dtype, ...)				\
	typedef struct {						\
		size_t size, size_ul, size_con;				\
		dstack(size_t) *st;					\
		__stl_unorderedlist_t *uelems;				\
		__stl_linkedlist_t *linked;				\
		STL_DCONTAINER(1, dtype) con;				\
	} __stl_dlist_t_ptr_ ## dtype

#define __stl_def_dlist(dtype, ...)					\
	typedef struct {						\
		size_t size, size_ul, size_con;				\
		dstack(size_t) *st;					\
		__stl_unorderedlist_t *uelems;				\
		__stl_linkedlist_t *linked;				\
		STL_DCONTAINER(0, dtype) con; \
	} __stl_dlist_t_ ## dtype

#define def_dlist(dtype)				\
	STL_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_def_ptr_dlist(dtype))		\
	     (__stl_def_dlist(dtype))


#define __stl_list_ptr(one, dtype, ...)				\
	__stl_list_t_ptr_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__
#define __stl_list(dtype, ...)					\
	__stl_list_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define list(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_list_ptr(dtype __VA_OPT__(,) __VA_ARGS__))		\
	     (__stl_list(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_dlist_ptr(one, dtype)				\
	__stl_dlist_t_ptr_ ## dtype 
#define __stl_dlist(dtype)			\
	__stl_dlist_t_ ## dtype

#define dlist(dtype)					\
	STL_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_dlist_ptr(dtype))			\
	     (__stl_dlist(dtype))

#define list_init(list, ...)						\
	do {								\
		(list).size_con = (list).size_ul = (list).size = 0;	\
		STL_INIT_D_CONTAINER_DTYPE_SIZE((list).con, (list).con.container[0]); \
		STL_INIT_D_CONTAINER_ST_SIZE((list).con, (list));	\
		STL_INIT_D_CONTAINER_CAPACITY((list).con);		\
		(list).uelems = (list).__ulist_alloc;			\
		(list).linked = (list).__linked_alloc;			\
		(list).st = &(list).__st_alloc;				\
		stack_init(*(list).st);					\
		(list).container = (list).con.container;		\
	} while (0)

#define list_size(list) (list).size
#define list_empty(list) ((list).size == 0)
#define list_capacity(list) (list).con.capacity
#define list_append(list, item)						\
	(list).con.container[list_insert_byindex((__stl_list_t *) &(list), (list).size)] = item
#define list_insert(list, item, index)					\
	(list).con.container[list_insert_byindex((__stl_list_t *) &(list), index)] = item
#define list_pop(list)							\
	(list).con.container[list_remove_byindex((__stl_list_t *) &(list), (list).size - 1)]
#define list_index(list, index)						\
	(list).con.container[list_fetch_byindex((__stl_list_t *) &(list), index)]
#define list_erase(list, index)						\
	(list).con.container[list_remove_byindex((__stl_list_t *) &(list), index)]

extern size_t list_fetch_byindex(__stl_list_t *list, size_t ind);
extern size_t list_remove_byindex(__stl_list_t *list, size_t ind);
extern size_t list_insert_byindex(__stl_list_t *list, size_t ind);

#endif
