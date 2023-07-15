#ifndef PAIR_INCLUDED
#define PAIR_INCLUDED

#include <stddef.h>
#include "def.h"

typedef struct {
	unsigned char *addr_first, *addr_second;
	size_t size_first, size_second;
} __stl_pair_t;

#define __stl_pair_ptr(one, dtype, ...)		\
	dtype *

#define __stl_pair(dtype, ...)			\
	dtype

#define __def_pair(first_dtype, second_dtype)				\
	typedef struct {						\
		first_dtype *addr_first;				\
		second_dtype *addr_second;				\
		size_t size_first, size_second;				\
		first_dtype first;					\
		second_dtype second;					\
	} __stl_pair_t_ ## first_dtype ## _ ## second_dtype

#define __def_pair_ptr_first(one, first_dtype, second_dtype)		\
	typedef struct {						\
		first_dtype **addr_first;				\
		second_dtype *addr_second;				\
		size_t size_first, size_second;				\
		first_dtype *first;					\
		second_dtype second;					\
	} __stl_pair_t_ptr_ ## first_dtype ## _ ## second_dtype

#define __def_pair_ptr_second(first_dtype, one, second_dtype)		\
	typedef struct {						\
		first_dtype *addr_first;				\
		second_dtype **addr_second;				\
		size_t size_first, size_second;				\
		first_dtype first;					\
		second_dtype *second;					\
	} __stl_pair_t_ ## first_dtype ## _ptr_ ## second_dtype

#define __def_pair_ptr_first_ptr_second(one, first_dtype, one2, second_dtype) \
	typedef struct {						\
		first_dtype **addr_first;				\
		second_dtype **addr_second;				\
		size_t size_first, size_second;				\
		first_dtype *first;					\
		second_dtype *second;					\
	} __stl_pair_t_ptr_ ## first_dtype ## _ptr_ ## second_dtype

#define def_pair(first_dtype, second_dtype)		\
	STL_IF_ELSE_PTR_DTYPE(first_dtype)		\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__def_pair_ptr_first_ptr_second(first_dtype, second_dtype)) \
	      (__def_pair_ptr_first(first_dtype, second_dtype)))	\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)\
	      (__def_pair_ptr_second(first_dtype, second_dtype))	\
	      (__def_pair(first_dtype, second_dtype)))

#define __pair(first_dtype, second_dtype)			\
	__stl_pair_t_ ## first_dtype ## _ ## second_dtype
#define __pair_ptr_first(one, first_dtype, second_dtype)	\
	__stl_pair_t_ptr_ ## first_dtype ## _ ## second_dtype
#define __pair_ptr_second(first_dtype, one, second_dtype)	\
	__stl_pair_t_ ## first_dtype ## _ptr_ ## second_dtype
#define __pair_ptr_first_ptr_second(one, first_dtype, one2, second_dtype) \
	__stl_pair_t_ptr_ ## first_dtype ## _ptr_ ## second_dtype
	
#define pair(first_dtype, second_dtype)				       \
	STL_IF_ELSE_PTR_DTYPE(first_dtype)			       \
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)		       \
	      (__pair_ptr_first_ptr_second(first_dtype, second_dtype)) \
	      (__pair_ptr_first(first_dtype, second_dtype)))	       \
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)		       \
	      (__pair_ptr_second(first_dtype, second_dtype))	       \
	      (__pair(first_dtype, second_dtype)))

#define init_pair(pair, f, s)				\
	do {						\
		(pair).first = f;			\
		(pair).addr_first = &((pair).first);	\
		(pair).size_first = sizeof(f);		\
		(pair).second = s;			\
		(pair).addr_second = &((pair).second);	\
		(pair).size_second = sizeof(s);		\
	} while (0)

#define pair_first(pair)			\
	(pair).first

#define pair_second(pair)			\
	(pair).second

#endif

