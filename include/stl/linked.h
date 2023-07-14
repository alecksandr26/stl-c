/*!
  @file linked.h
  @brief This library provides a linked list ADT implementation.

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef LINKED_INCLUDED
#define LINKED_INCLUDED

#include "con.h"
#include "mem.h"
#include "def.h"
#include "init.h"
#include "iter.h"

#define STL_DEFAULT_LINKED_CAPACITY STL_DEFAULT_CONTAINER_CAPACITY
#define STL_DEFAULT_DLINKED_INCREASE_RATE STL_DEFAULT_DCONTAINER_INCREASE_RATE

typedef struct __stl_link_node_t {
	int next, prev;
} __stl_link_node_t;

typedef struct {
	__stl_linked_type type;
	int front, back, deleted_head;
	__stl_link_node_t *links;
	__stl_con_t con;
} __stl_linked_t;

#define __stl_def_ptr_linked(one, dtype, ...)				\
	typedef struct {						\
		__stl_linked_type type;					\
		int front, back, deleted_head;				\
		__stl_link_node_t *links;				\
		STL_CONTAINER(1, dtype, STL_DEFAULT_LINKED_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
		__stl_link_node_t alloc_links[__STL_CONTAINER_SELECT_CAPACITY(__VA_ARGS__ \
									      __VA_OPT__(,) \
									      STL_DEFAULT_LINKED_CAPACITY)]; \
	} __stl_linked_t_ptr_ ## dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define __stl_def_linked(dtype, ...)					\
	typedef struct {						\
		__stl_linked_type type;					\
		int front, back, deleted_head;				\
		__stl_link_node_t *links;				\
		STL_CONTAINER(0, dtype, STL_DEFAULT_LINKED_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
		__stl_link_node_t alloc_links[__STL_CONTAINER_SELECT_CAPACITY(__VA_ARGS__ \
									      __VA_OPT__(,) \
									      STL_DEFAULT_LINKED_CAPACITY)]; \
	} __stl_linked_t_ ## dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define def_linked(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_def_ptr_linked(dtype __VA_OPT__(,) __VA_ARGS__))	\
	     (__stl_def_linked(dtype __VA_OPT__(,) __VA_ARGS__))


#define __stl_def_ptr_dlinked(one, dtype, ...)				\
	typedef struct {						\
		__stl_linked_type type;					\
		int front, back, deleted_head;				\
		__stl_link_node_t *links;				\
		STL_DCONTAINER(1, dtype) con;				\
		__stl_link_node_t *alloc_links;				\
	} __stl_dlinked_t_ptr_ ## dtype

#define __stl_def_dlinked(dtype, ...)					\
	typedef struct {						\
		__stl_linked_type type;					\
		int front, back, deleted_head;				\
		__stl_link_node_t *links;				\
		STL_DCONTAINER(0, dtype) con;				\
		__stl_link_node_t *alloc_links;				\
	} __stl_dlinked_t_ ## dtype


#define def_dlinked(dtype)				\
	STL_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_def_ptr_dlinked(dtype))		\
	     (__stl_def_dlinked(dtype))

#define __stl_linked_ptr(one, dtype, ...)					\
	__stl_linked_t_ptr_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__
#define __stl_linked(dtype, ...)				\
	__stl_linked_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define linked(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_linked_ptr(dtype __VA_OPT__(,) __VA_ARGS__))		\
	     (__stl_linked(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_dlinked_ptr(one, dtype)		\
	__stl_dlinked_t_ptr_ ## dtype 
#define __stl_dlinked(dtype)			\
	__stl_dlinked_t_ ## dtype

#define dlinked(dtype)					\
	STL_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_dlinked_ptr(dtype))			\
	     (__stl_dlinked(dtype))

#define linked_front(linked)						\
	(linked).con.container[__stl_linked_front((__stl_linked_t *) &(linked))]

#define linked_back(linked)			\
	(linked).con.container[__stl_linked_back((__stl_linked_t *) &(linked))]

#define linked_push_back(linked, item)					\
	*((typeof((linked).con.container[0]) *)				\
	  __stl_linked_ins_after_byindex((__stl_linked_t *) &(linked),	\
					 ((linked).con.size == 0)	\
					 ? 0				\
					 : __stl_linked_back((__stl_linked_t *) &(linked)))) = item

#define linked_push_front(linked, item)					\
	*((typeof((linked).con.container[0]) *)				\
	  __stl_linked_ins_prev_byindex((__stl_linked_t *) &(linked),	\
					((linked).con.size == 0)	\
					? -1				\
					: __stl_linked_front((__stl_linked_t *) &(linked)))) = item

#define linked_pop_back(linked)						\
	*((typeof((linked).con.container[0]) *)				\
	  __stl_linked_rem_byindex((__stl_linked_t *) &(linked),	\
				   __stl_linked_back((__stl_linked_t *) &(linked))))

#define linked_pop_front(linked)					\
	*((typeof((linked).con.container[0]) *)				\
	__stl_linked_rem_byindex((__stl_linked_t *) &(linked),		\
				 __stl_linked_front((__stl_linked_t *) &(linked))))

#define linked_at(linked, index)					\
	(linked).con.container[__stl_linked_at((__stl_linked_t *) &(linked), index)]

#define linked_ins(linked, index, item)					\
	*((typeof((linked).con.container[0]) *)				\
	  __stl_linked_ins_prev_byindex((__stl_linked_t *) &(linked),	\
				       __stl_linked_at((__stl_linked_t *) &(linked), index))) = item

#define linked_rem(linked, index)					\
	*((typeof((linked).con.container[0]) *)				\
	  __stl_linked_rem_byindex((__stl_linked_t *) &(linked),	\
				   __stl_linked_at((__stl_linked_t *) &(linked), index)))

#define linked_begin(linked, iter)					\
	__stl_linked_begin((__stl_linked_t *) &(linked), (__stl_iter_t *) &(iter))

#define linked_end(linked, iter)					\
	__stl_linked_end((__stl_linked_t *) &(linked), (__stl_iter_t *) &(iter))

extern unsigned char *__stl_linked_ins_after_byindex(__stl_linked_t *linked, int index);
extern unsigned char *__stl_linked_ins_prev_byindex(__stl_linked_t *linked, int index);
extern unsigned char *__stl_linked_rem_byindex(__stl_linked_t *linked, size_t curr);
extern size_t __stl_linked_front(__stl_linked_t *linked);
extern size_t __stl_linked_back(__stl_linked_t *linked);
extern size_t __stl_linked_at(__stl_linked_t *linked, size_t index);
extern void __stl_linked_begin(__stl_linked_t *linked, __stl_iter_t *iter);
extern void __stl_linked_end(__stl_linked_t *linked, __stl_iter_t *iter);

#endif
