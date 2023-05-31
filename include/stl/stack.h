/*!
  @file stack.h
  @brief Stacks are a type of container adaptor, specifically designed to operate in a
  LIFO context (last-in first-out), where elements are inserted and extracted only from
  one end of the container.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#include <stddef.h>

#include "con.h"
#include "mem.h"
#include "def.h"

#define STL_DEFAULT_STACK_CAPACITY STL_DEFAULT_CONTAINER_CAPACITY
#define STL_DEFAULT_DSTACK_CAPACITY STL_DEFAULT_DCONTAINER_CAPACITY
#define STL_DEFAULT_DSTACK_INCREASE_RATE STL_DEFAULT_DCONTAINER_INCREASE_RATE

typedef struct {
	size_t head;
	__stl_con_t con;
} __stl_stack_t;

#define __stl_def_ptr_stack(one, dtype, ...)	\
	typedef struct {	 \
		size_t head;	 \
		STL_CONTAINER(1, dtype, STL_DEFAULT_STACK_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
	} __stl_stack_t_ptr_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define __stl_def_stack(dtype, ...)	\
	typedef struct {	 \
		size_t head;	 \
		STL_CONTAINER(0, dtype, STL_DEFAULT_STACK_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
	} __stl_stack_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define def_stack(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     (__stl_def_ptr_stack(dtype __VA_OPT__(,) __VA_ARGS__))	\
	     (__stl_def_stack(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_def_ptr_dstack(one, dtype)	\
	typedef struct {	 \
		size_t head;	 \
		STL_DCONTAINER(1, dtype) con; \
	} __stl_dstack_t_ptr_ ## dtype

#define __stl_def_dstack(dtype)			\
	typedef struct {			\
		size_t head;			\
		STL_DCONTAINER(0, dtype) con;	\
	} __stl_dstack_t_ ## dtype 


#define def_dstack(dtype)			\
	STL_IF_ELSE_PTR_DTYPE(dtype)		\
	     (__stl_def_ptr_dstack(dtype))	\
	     (__stl_def_dstack(dtype))

#define __stl_stack_ptr(one, dtype, ...)				\
	__stl_stack_t_ptr_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define __stl_stack(dtype, ...)			\
	__stl_stack_t_ ## dtype ## __VA_OPT__(_) ## __VA_ARGS__

#define stack(dtype, ...)					\
	STL_IF_ELSE_PTR_DTYPE(dtype)				\
	     (__stl_stack_ptr(dtype __VA_OPT__(,) __VA_ARGS__))	\
	     (__stl_stack(dtype __VA_OPT__(,) __VA_ARGS__))

#define __stl_dstack_ptr(one, dtype)		\
	__stl_dstack_t_ptr_ ## dtype 

#define __stl_dstack(dtype)			\
	__stl_dstack_t_ ## dtype 

#define dstack(dtype)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)				\
	     (__stl_dstack_ptr(dtype))				\
	     (__stl_dstack(dtype))

#define new_dstack(dtype, ...)						\
	STL_IF_ELSE_PTR_DTYPE(dtype)					\
	     ((__stl_dstack_ptr(dtype) *))				\
	     ((__stl_dstack(dtype) *))					\
	     stl_alloc_struct(STL_IF_ELSE_PTR_DTYPE(dtype)		\
			      (sizeof(__stl_dstack_ptr(dtype)))		\
			      (sizeof(__stl_dstack(dtype))),		\
			      STL_IF_ELSE_PTR_DTYPE(dtype)(sizeof(_STL_SECOND(dtype) *))(sizeof(dtype)) \
			      * __STL_CONTAINER_SELECT_SIZE(__VA_ARGS__ __VA_OPT__(,) \
							    STL_DEFAULT_DSTACK_CAPACITY))

#define stack_init(stack, ...)				\
	do {						\
		(stack).head = 0;			\
		STL_INIT_D_CONTAINER_DTYPE_SIZE((stack).con, (stack).con.container[0]); \
		STL_INIT_D_CONTAINER_ST_SIZE((stack).con, (stack));	\
		STL_INIT_D_CONTAINER_CAPACITY((stack).con);		\
	} while (0)

#define stack_push(stack, item) (stack).con.container[stl_stack_inc((__stl_stack_t *) &(stack))] = item
#define stack_top(stack) (stack).con.container[stl_stack_top((__stl_stack_t *) &(stack))]
#define stack_pop(stack) (stack).con.container[stl_stack_dec((__stl_stack_t *) &(stack))]
#define stack_size(stack) (stack).head
#define stack_capacity(stack) (stack).con.capacity
#define stack_empty(stack) ((stack).head == 0)
#define dstack_push(dstack, item)					\
	*((typeof(dstack->con.container[0]) *) stl_dstack_inc((__stl_stack_t *) dstack)) = item
#define dstack_pop(dstack) *((typeof(dstack->con.container[0]) *) stl_dstack_dec((__stl_stack_t *) dstack))
#define dstack_top(dstack) stack_top(*dstack)
#define dstack_init(dstack) stack_init(*dstack)
#define dstack_size(dstack) stack_size(*dstack)
#define dstack_empty(dstack) stack_empty(*dstack)
#define dstack_capacity(dstack) stack_capacity(*dstack)

extern Except NotEnoughCapacityAtStructure, EmptyStructure;
extern size_t stl_stack_inc(__stl_stack_t *stack);
extern size_t stl_stack_dec(__stl_stack_t *stack);
extern size_t stl_stack_top(__stl_stack_t *stack);
extern unsigned char *stl_dstack_inc(__stl_stack_t *stack);
extern unsigned char *stl_dstack_dec(__stl_stack_t *stack);

#define mul_def_stack(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack1(dtype, __VA_ARGS__))
#define mul_def_stack1(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack2(dtype, __VA_ARGS__))
#define mul_def_stack2(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack3(dtype, __VA_ARGS__))
#define mul_def_stack3(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack4(dtype, __VA_ARGS__))
#define mul_def_stack4(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack5(dtype, __VA_ARGS__))
#define mul_def_stack5(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack6(dtype, __VA_ARGS__))
#define mul_def_stack6(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack7(dtype, __VA_ARGS__))
#define mul_def_stack7(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack8(dtype, __VA_ARGS__))
#define mul_def_stack8(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack9(dtype, __VA_ARGS__))
#define mul_def_stack9(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack10(dtype, __VA_ARGS__))
#define mul_def_stack10(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack11(dtype, __VA_ARGS__))
#define mul_def_stack11(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack12(dtype, __VA_ARGS__))
#define mul_def_stack12(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack13(dtype, __VA_ARGS__))
#define mul_def_stack13(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack14(dtype, __VA_ARGS__))
#define mul_def_stack14(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack15(dtype, __VA_ARGS__))
#define mul_def_stack15(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack16(dtype, __VA_ARGS__))
#define mul_def_stack16(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack17(dtype, __VA_ARGS__))
#define mul_def_stack17(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack18(dtype, __VA_ARGS__))
#define mul_def_stack18(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack19(dtype, __VA_ARGS__))
#define mul_def_stack19(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack20(dtype, __VA_ARGS__))
#define mul_def_stack20(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack21(dtype, __VA_ARGS__))
#define mul_def_stack21(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack22(dtype, __VA_ARGS__))
#define mul_def_stack22(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack23(dtype, __VA_ARGS__))
#define mul_def_stack23(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack24(dtype, __VA_ARGS__))
#define mul_def_stack24(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack25(dtype, __VA_ARGS__))
#define mul_def_stack25(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack26(dtype, __VA_ARGS__))
#define mul_def_stack26(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack27(dtype, __VA_ARGS__))
#define mul_def_stack27(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack28(dtype, __VA_ARGS__))
#define mul_def_stack28(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack29(dtype, __VA_ARGS__))
#define mul_def_stack29(dtype, X, ...) def_stack(dtype, X) __VA_OPT__(; mul_def_stack30(dtype, __VA_ARGS__))
#define mul_def_stack30(dtype, X, ...) def_stack(dtype, X)

#define mul_def_dstack(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack1(__VA_ARGS__))
#define mul_def_dstack1(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack2(__VA_ARGS__))
#define mul_def_dstack2(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack3(__VA_ARGS__))
#define mul_def_dstack3(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack4(__VA_ARGS__))
#define mul_def_dstack4(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack5(__VA_ARGS__))
#define mul_def_dstack5(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack6(__VA_ARGS__))
#define mul_def_dstack6(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack7(__VA_ARGS__))
#define mul_def_dstack7(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack8(__VA_ARGS__))
#define mul_def_dstack8(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack9(__VA_ARGS__))
#define mul_def_dstack9(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack10(__VA_ARGS__))
#define mul_def_dstack10(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack11(__VA_ARGS__))
#define mul_def_dstack11(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack12(__VA_ARGS__))
#define mul_def_dstack12(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack13(__VA_ARGS__))
#define mul_def_dstack13(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack14(__VA_ARGS__))
#define mul_def_dstack14(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack15(__VA_ARGS__))
#define mul_def_dstack15(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack16(__VA_ARGS__))
#define mul_def_dstack16(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack17(__VA_ARGS__))
#define mul_def_dstack17(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack18(__VA_ARGS__))
#define mul_def_dstack18(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack19(__VA_ARGS__))
#define mul_def_dstack19(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack20(__VA_ARGS__))
#define mul_def_dstack20(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack21(__VA_ARGS__))
#define mul_def_dstack21(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack22(__VA_ARGS__))
#define mul_def_dstack22(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack23(__VA_ARGS__))
#define mul_def_dstack23(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack24(__VA_ARGS__))
#define mul_def_dstack24(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack25(__VA_ARGS__))
#define mul_def_dstack25(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack26(__VA_ARGS__))
#define mul_def_dstack26(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack27(__VA_ARGS__))
#define mul_def_dstack27(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack28(__VA_ARGS__))
#define mul_def_dstack28(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack29(__VA_ARGS__))
#define mul_def_dstack29(dtype, ...) def_dstack(dtype) __VA_OPT__(; mul_def_dstack30(__VA_ARGS__))
#define mul_def_dstack30(dtype, ...) def_dstack(dtype)

#endif
