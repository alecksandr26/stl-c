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

#define __stl_def_queue(dtype, ...)		\
	typedef struct {				\
		int rear, front;					\
		size_t size;						\
		STL_CONTAINER(0, dtype, STL_DEFAULT_QUEUE_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
	} __stl_queue_t_ ## dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define def_queue(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_def_ptr_queue(dtype __VA_OPT__(,) __VA_ARGS__))	\
	     (__stl_def_queue(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_def_ptr_dqueue(one, dtype, ...)				\
	typedef struct {						\
		int rear, front;					\
		size_t size;						\
		STL_DCONTAINER(1, dtype) con;				\
	} __stl_dqueue_t_ptr_ ## dtype

#define __stl_def_dqueue(dtype, ...)					\
	typedef struct {						\
		int rear, front;					\
		size_t size;						\
		STL_DCONTAINER(0, dtype) con;				\
	} __stl_dqueue_t_ ## dtype

#define def_dqueue(dtype)				\
	STL_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_def_ptr_dqueue(dtype))		\
	     (__stl_def_dqueue(dtype))

#define __stl_queue_ptr(one, dtype, ...)				\
	__stl_queue_t_ptr_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__
#define __stl_queue(dtype, ...)				\
	__stl_queue_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define queue(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_queue_ptr(dtype __VA_OPT__(,) __VA_ARGS__))		\
	     (__stl_queue(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_dqueue_ptr(one, dtype)				\
	__stl_dqueue_t_ptr_ ## dtype 
#define __stl_dqueue(dtype)				\
	__stl_dqueue_t_ ## dtype 

#define dqueue(dtype)				\
	STL_IF_ELSE_PTR_DTYPE(dtype)			\
	     (__stl_dqueue_ptr(dtype))			\
	     (__stl_dqueue(dtype))

#define new_dqueue(dtype, ...)			\
	STL_IF_ELSE_PTR_DTYPE(dtype)\
	     ((__stl_dqueue_ptr(dtype) *))	\
	     ((__stl_dqueue(dtype) *))				\
	     stl_alloc_struct(STL_IF_ELSE_PTR_DTYPE(dtype)\
			      (sizeof(__stl_dqueue_ptr(dtype)))		\
			      (sizeof(__stl_dqueue(dtype))),		\
			      STL_IF_ELSE_PTR_DTYPE(dtype)(sizeof(__STL_SECOND(dtype) *))(sizeof(dtype)) \
			      * __STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) \
							    STL_DEFAULT_DQUEUE_CAPACITY))

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
#define queue_push(queue, item) (queue).con.container[stl_queue_inc((__stl_queue_t *) &(queue))] = item
#define queue_pop(queue) (queue).con.container[stl_queue_dec((__stl_queue_t *) &(queue))]
#define dqueue_init(dqueue, ...) queue_init(*dqueue __VA_OPT__(,) __VA_ARGS__)
#define dqueue_empty(queue) queue_size(*dqueue)
#define dqueue_capacity(queue) queue_capacity(*dqueue)
#define dqueue_size(dqueue) queue_size(*dqueue)
#define dqueue_push(dqueue, item)					\
	*((typeof(dqueue->con.container[0]) *) stl_dqueue_inc((__stl_queue_t *) dqueue)) = item
#define dqueue_pop(dqueue) *((typeof(dqueue->con.container[0]) *) stl_dqueue_dec((__stl_queue_t *) dqueue))
#define dqueue_front(dqueue) queue_front(*dqueue)
#define dqueue_back(dqueue) queue_back(*dqueue)

extern size_t stl_queue_inc(__stl_queue_t *queue);
extern size_t stl_queue_dec(__stl_queue_t *queue);
extern size_t stl_queue_front(__stl_queue_t *queue);
extern size_t stl_queue_back(__stl_queue_t *queue);
extern unsigned char *stl_dqueue_inc(__stl_queue_t *stack);
extern unsigned char *stl_dqueue_dec(__stl_queue_t *stack);

#define mul_def_queue(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue1(dtype, __VA_ARGS__))
#define mul_def_queue1(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue2(dtype, __VA_ARGS__))
#define mul_def_queue2(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue3(dtype, __VA_ARGS__))
#define mul_def_queue3(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue4(dtype, __VA_ARGS__))
#define mul_def_queue4(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue5(dtype, __VA_ARGS__))
#define mul_def_queue5(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue6(dtype, __VA_ARGS__))
#define mul_def_queue6(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue7(dtype, __VA_ARGS__))
#define mul_def_queue7(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue8(dtype, __VA_ARGS__))
#define mul_def_queue8(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue9(dtype, __VA_ARGS__))
#define mul_def_queue9(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue10(dtype, __VA_ARGS__))
#define mul_def_queue10(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue11(dtype, __VA_ARGS__))
#define mul_def_queue11(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue12(dtype, __VA_ARGS__))
#define mul_def_queue12(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue13(dtype, __VA_ARGS__))
#define mul_def_queue13(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue14(dtype, __VA_ARGS__))
#define mul_def_queue14(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue15(dtype, __VA_ARGS__))
#define mul_def_queue15(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue16(dtype, __VA_ARGS__))
#define mul_def_queue16(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue17(dtype, __VA_ARGS__))
#define mul_def_queue17(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue18(dtype, __VA_ARGS__))
#define mul_def_queue18(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue19(dtype, __VA_ARGS__))
#define mul_def_queue19(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue20(dtype, __VA_ARGS__))
#define mul_def_queue20(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue21(dtype, __VA_ARGS__))
#define mul_def_queue21(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue22(dtype, __VA_ARGS__))
#define mul_def_queue22(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue23(dtype, __VA_ARGS__))
#define mul_def_queue23(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue24(dtype, __VA_ARGS__))
#define mul_def_queue24(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue25(dtype, __VA_ARGS__))
#define mul_def_queue25(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue26(dtype, __VA_ARGS__))
#define mul_def_queue26(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue27(dtype, __VA_ARGS__))
#define mul_def_queue27(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue28(dtype, __VA_ARGS__))
#define mul_def_queue28(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue29(dtype, __VA_ARGS__))
#define mul_def_queue29(dtype, X, ...) def_queue(dtype, X) __VA_OPT__(; mul_def_queue30(dtype, __VA_ARGS__))
#define mul_def_queue30(dtype, X, ...) def_queue(dtype, X)

#define mul_def_dqueue(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue1(__VA_ARGS__))
#define mul_def_dqueue1(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue2(__VA_ARGS__))
#define mul_def_dqueue2(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue3(__VA_ARGS__))
#define mul_def_dqueue3(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue4(__VA_ARGS__))
#define mul_def_dqueue4(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue5(__VA_ARGS__))
#define mul_def_dqueue5(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue6(__VA_ARGS__))
#define mul_def_dqueue6(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue7(__VA_ARGS__))
#define mul_def_dqueue7(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue8(__VA_ARGS__))
#define mul_def_dqueue8(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue9(__VA_ARGS__))
#define mul_def_dqueue9(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue10(__VA_ARGS__))
#define mul_def_dqueue10(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue11(__VA_ARGS__))
#define mul_def_dqueue11(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue12(__VA_ARGS__))
#define mul_def_dqueue12(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue13(__VA_ARGS__))
#define mul_def_dqueue13(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue14(__VA_ARGS__))
#define mul_def_dqueue14(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue15(__VA_ARGS__))
#define mul_def_dqueue15(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue16(__VA_ARGS__))
#define mul_def_dqueue16(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue17(__VA_ARGS__))
#define mul_def_dqueue17(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue18(__VA_ARGS__))
#define mul_def_dqueue18(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue19(__VA_ARGS__))
#define mul_def_dqueue19(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue20(__VA_ARGS__))
#define mul_def_dqueue20(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue21(__VA_ARGS__))
#define mul_def_dqueue21(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue22(__VA_ARGS__))
#define mul_def_dqueue22(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue23(__VA_ARGS__))
#define mul_def_dqueue23(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue24(__VA_ARGS__))
#define mul_def_dqueue24(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue25(__VA_ARGS__))
#define mul_def_dqueue25(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue26(__VA_ARGS__))
#define mul_def_dqueue26(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue27(__VA_ARGS__))
#define mul_def_dqueue27(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue28(__VA_ARGS__))
#define mul_def_dqueue28(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue29(__VA_ARGS__))
#define mul_def_dqueue29(dtype, ...) def_dqueue(dtype) __VA_OPT__(; mul_def_dqueue30(__VA_ARGS__))
#define mul_def_dqueue30(dtype, ...) def_dqueue(dtype)

#endif
