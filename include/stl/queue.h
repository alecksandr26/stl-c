/*!
  @file queue.h
  @brief A Queue is defined as a linear data structure that is open at both ends and the
  operations are performed in First In First Out (FIFO) order.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/
#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

#include "con.h"
#include "mem.h"
#include "def.h"

#define STL_DEFAULT_QUEUE_CAPACITY STL_DEFAULT_CONTAINER_CAPACITY
#define STL_DEFAULT_DQUEUE_CAPACITY STL_DEFAULT_DCONTAINER_CAPACITY
#define STL_DEFAULT_DQUEUE_INCREASE_RATE STL_DEFAULT_DCONTAINER_INCREASE_RATE

typedef struct {
	int rear, front;
	size_t size;
	__stl_con_t con;
} __stl_queue_t;

#define __stl_def_ptr_queue(one, dtype, ...)		\
	typedef struct {						\
		int rear, front;					\
		size_t size;						\
		STL_CONTAINER(1, dtype, STL_DEFAULT_QUEUE_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
	} __stl_queue_t_ptr_ ## dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define __stl_def_re_queue(dtype, ...)		\
	typedef struct {				\
		int rear, front;					\
		size_t size;						\
		STL_CONTAINER(0, dtype, STL_DEFAULT_QUEUE_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
	} __stl_queue_t_ ## dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define def_queue(dtype, ...)						\
	SLT_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_def_ptr_queue(dtype __VA_OPT__(,) __VA_ARGS__))	\
	     (__stl_def_re_queue(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_def_ptr_dqueue(one, dtype, ...)				\
	typedef struct {						\
		int rear, front;					\
		size_t size;						\
		STL_DCONTAINER(1, dtype) con;				\
	} __stl_dqueue_t_ptr_ ## dtype

#define __stl_def_re_dqueue(dtype, ...)					\
	typedef struct {						\
		int rear, front;					\
		size_t size;						\
		STL_DCONTAINER(0, dtype) con;				\
	} __stl_dqueue_t_ ## dtype

#define def_dqueue(dtype)				\
	SLT_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_def_ptr_dqueue(dtype))		\
	     (__stl_def_re_dqueue(dtype))

#define __stl_queue_ptr(one, dtype, ...)				\
	__stl_queue_t_ptr_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__
#define __stl_queue_re(dtype, ...)				\
	__stl_queue_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define queue(dtype, ...)						\
	SLT_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_queue_ptr(dtype __VA_OPT__(,) __VA_ARGS__))		\
	     (__stl_queue_re(dtype __VA_OPT__(,) __VA_ARGS__))


#define __stl_dqueue_ptr(one, dtype)				\
	__stl_dqueue_t_ptr_ ## dtype 
#define __stl_dqueue_re(dtype)				\
	__stl_dqueue_t_ ## dtype 

#define dqueue(dtype)				\
	SLT_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_dqueue_ptr(dtype))			\
	     (__stl_dqueue_re(dtype))

#define new_dqueue(dtype, ...)						\
	SLT_IF_ELSE_PTR_DTYPE(dtype)\
	     ((__stl_dqueue_ptr(dtype) *))	\
	     ((__stl_dqueue_re(dtype) *))				\
	     stl_alloc_struct(SLT_IF_ELSE_PTR_DTYPE(dtype)\
			      (sizeof(__stl_dqueue_ptr(dtype)))		\
			      (sizeof(__stl_dqueue_re(dtype))),		\
			 SLT_IF_ELSE_PTR_DTYPE(dtype)(sizeof(__STL_SECOND(dtype)))(sizeof(dtype)) \
			 * __STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) STL_DEFAULT_DQUEUE_CAPACITY))

#define queue_init(queue, ...)						\
	do {								\
		(queue).size = 0;					\
		(queue).rear = (queue).front = -1;			\
		STL_INIT_D_CONTAINER_DTYPE_SIZE((queue).con, (queue).con.container[0]); \
		STL_INIT_D_CONTAINER_ST_SIZE((queue).con, (queue));	\
		STL_INIT_D_CONTAINER_CAPACITY((queue).con);		\
	} while (0)

#define queue_empty(queue) ((queue).size == 0)
#define queue_size(queue) (queue).size
#define queue_capacity(queue) STL_CONTAINER_CAPACITY((queue).con)
#define queue_front(queue) (queue).con.container[stl_queue_front((__stl_queue_t *) &(queue))]
#define queue_back(queue) (queue).con.container[stl_queue_back((__stl_queue_t *) &(queue))]
#define queue_push(queue, item)						\
	(queue).con.container[stl_queue_inc((__stl_queue_t *) &(queue))] = item
#define queue_pop(queue)			\
	(queue).con.container[stl_queue_dec((__stl_queue_t *) &(queue))]

#define dqueue_init(dqueue, ...) queue_init(*dqueue __VA_OPT__(,) __VA_ARGS__)
#define dqueue_empty(queue) queue_size(*dqueue)
#define dqueue_capacity(queue) queue_capacity(*dqueue)
#define dqueue_push(dqueue, item) \
	*((typeof(dqueue->con.container[0]) *) stl_dqueue_inc((__stl_queue_t *) dqueue)) = item

extern size_t stl_queue_inc(__stl_queue_t *queue);
extern size_t stl_queue_dec(__stl_queue_t *queue);
extern size_t stl_queue_front(__stl_queue_t *queue);
extern size_t stl_queue_back(__stl_queue_t *queue);
extern unsigned char *stl_dqueue_inc(__stl_queue_t *stack);
extern unsigned char *stl_dqueue_dec(__stl_queue_t *stack);

#endif
