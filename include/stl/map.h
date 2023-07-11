
#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include "con.h"
#include "mem.h"
#include "def.h"
#include "init.h"
#include "linked.h"
#include "pair.h"

#define STL_DEFAULT_MAP_CAPACITY STL_DEFAULT_CONTAINER_CAPACITY
#define STL_DEFAULT_DMAP_INCREASE_RATE STL_DEFAULT_DCONTAINER_INCREASE_RATE
#define STL_DEFAULT_MAP_LINKED_CAPACITY 50

typedef struct {
	__stl_map_type type;
	__stl_con_t con;
} __stl_map_t;

#define __def_map(first_dtype, second_dtype, ...)			\
	typedef struct {						\
		__stl_map_type type;					\
		STL_CONTAINER(0, linked(pair(first_dtype, second_dtype), \
					     STL_DEFAULT_MAP_LINKED_CAPACITY),	\
			      STL_DEFAULT_LINKED_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
	} __stl_map_t_ ## first_dtype ## _ ## second_dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define __def_map_ptr_first(one, first_dtype, second_dtype, ...)	\
	typedef struct {						\
		__stl_map_type type;					\
		STL_CONTAINER(0, linked(pair(d_ptr(first_dtype), second_dtype),	\
					STL_DEFAULT_MAP_LINKED_CAPACITY), \
			      STL_DEFAULT_LINKED_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
	} __stl_map_t_ptr_ ## first_dtype ## _ ## second_dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define __def_map_ptr_second(first_dtype, one, second_dtype, ...)	\
	typedef struct {						\
		__stl_map_type type;					\
		STL_CONTAINER(0, linked(pair(first_dtype, d_ptr(second_dtype)),	\
					STL_DEFAULT_MAP_LINKED_CAPACITY), \
			      STL_DEFAULT_LINKED_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
	} __stl_map_t_ ## first_dtype ## _ptr_ ## second_dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define __def_map_ptr_first_ptr_second(one, first_dtype, one2, second_dtype, ...) \
	typedef struct {						\
		__stl_map_type type;					\
		STL_CONTAINER(0, linked(pair(d_ptr(first_dtype), d_ptr(second_dtype)), \
					STL_DEFAULT_MAP_LINKED_CAPACITY), \
			      STL_DEFAULT_LINKED_CAPACITY __VA_OPT__(,) __VA_ARGS__) con; \
	} __stl_map_t_ptr_ ## first_dtype ## _ptr_ ## second_dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define def_map(first_dtype, second_dtype, ...)				\
	STL_IF_ELSE_PTR_DTYPE(first_dtype)				\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__def_pair_ptr_first_ptr_second(first_dtype, second_dtype)) \
	      (__def_pair_ptr_first(first_dtype, second_dtype)))	\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__def_pair_ptr_second(first_dtype, second_dtype))	\
	      (__def_pair(first_dtype, second_dtype)));			\
	     def_linked(STL_IF_ELSE_PTR_DTYPE(first_dtype)		\
			(STL_IF_ELSE_PTR_DTYPE(second_dtype)		\
			 (__pair_ptr_first_ptr_second(first_dtype, second_dtype)) \
			 (__pair_ptr_first(first_dtype, second_dtype)))	\
			(STL_IF_ELSE_PTR_DTYPE(second_dtype)		\
			 (__pair_ptr_second(first_dtype, second_dtype))	\
			 (__pair(first_dtype, second_dtype))), STL_DEFAULT_MAP_LINKED_CAPACITY); \
        STL_IF_ELSE_PTR_DTYPE(first_dtype)				\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__def_map_ptr_first_ptr_second(first_dtype, second_dtype __VA_OPT__(,) __VA_ARGS__)) \
	      (__def_map_ptr_first(first_dtype, second_dtype __VA_OPT__(,) __VA_ARGS__))) \
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__def_map_ptr_second(first_dtype, second_dtype __VA_OPT__(,) __VA_ARGS__)) \
	      (__def_map(first_dtype, second_dtype __VA_OPT__(,) __VA_ARGS__)))

#define __map(first_dtype, second_dtype, ...)			\
	__stl_map_t_ ## first_dtype ## _ ## second_dtype ## __VA_OPT__(_) ##  __VA_ARGS__
#define __map_ptr_first(one, first_dtype, second_dtype, ...)	\
	__stl_map_t_ptr_ ## first_dtype ## _ ## second_dtype ## __VA_OPT__(_) ##  __VA_ARGS__
#define __map_ptr_second(first_dtype, one, second_dtype, ...)	\
	__stl_map_t_ ## first_dtype ## _ptr_ ## second_dtype ## __VA_OPT__(_) ##  __VA_ARGS__
#define __map_ptr_first_ptr_second(one, first_dtype, one2, second_dtype, ...) \
	__stl_map_t_ptr_ ## first_dtype ## _ptr_ ## second_dtype ## __VA_OPT__(_) ##  __VA_ARGS__

#define map(first_dtype, second_dtype, ...)				      \
	STL_IF_ELSE_PTR_DTYPE(first_dtype)			      \
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)		      \
	      (__map_ptr_first_ptr_second(first_dtype, second_dtype __VA_OPT__(,) __VA_ARGS__)) \
	      (__map_ptr_first(first_dtype, second_dtype __VA_OPT__(,) __VA_ARGS__)))	      \
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)		      \
	      (__map_ptr_second(first_dtype, second_dtype __VA_OPT__(,) __VA_ARGS__))	\
	      (__map(first_dtype, second_dtype __VA_OPT__(,) __VA_ARGS__)))

#define __def_dmap(first_dtype, second_dtype)			\
	typedef struct {						\
		__stl_map_type type;					\
		STL_DCONTAINER(0, linked(pair(first_dtype, second_dtype), \
					 STL_DEFAULT_MAP_LINKED_CAPACITY)) con; \
	} __stl_dmap_t_ ## first_dtype ## _ ## second_dtype

#define __def_dmap_ptr_first(one, first_dtype, second_dtype)	\
	typedef struct {						\
		__stl_map_type type;					\
		STL_DCONTAINER(0, linked(pair(d_ptr(first_dtype), second_dtype),	\
					 STL_DEFAULT_MAP_LINKED_CAPACITY)) con; \
	} __stl_dmap_t_ptr_ ## first_dtype ## _ ## second_dtype

#define __def_dmap_ptr_second(first_dtype, one, second_dtype)	\
	typedef struct {						\
		__stl_map_type type;					\
		STL_DCONTAINER(0, linked(pair(first_dtype, d_ptr(second_dtype)),	\
					STL_DEFAULT_MAP_LINKED_CAPACITY)) con; \
	} __stl_dmap_t_ ## first_dtype ## _ptr_ ## second_dtype

#define __def_dmap_ptr_first_ptr_second(one, first_dtype, one2, second_dtype) \
	typedef struct {						\
		__stl_map_type type;					\
		STL_DCONTAINER(0, linked(pair(d_ptr(first_dtype), d_ptr(second_dtype)), \
					STL_DEFAULT_MAP_LINKED_CAPACITY)) con; \
	} __stl_dmap_t_ptr_ ## first_dtype ## _ptr_ ## second_dtype

#define def_dmap(first_dtype, second_dtype)				\
	STL_IF_ELSE_PTR_DTYPE(first_dtype)				\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__def_pair_ptr_first_ptr_second(first_dtype, second_dtype)) \
	      (__def_pair_ptr_first(first_dtype, second_dtype)))	\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__def_pair_ptr_second(first_dtype, second_dtype))	\
	      (__def_pair(first_dtype, second_dtype)));			\
	     def_linked(STL_IF_ELSE_PTR_DTYPE(first_dtype)		\
			(STL_IF_ELSE_PTR_DTYPE(second_dtype)		\
			 (__pair_ptr_first_ptr_second(first_dtype, second_dtype)) \
			 (__pair_ptr_first(first_dtype, second_dtype)))	\
			(STL_IF_ELSE_PTR_DTYPE(second_dtype)		\
			 (__pair_ptr_second(first_dtype, second_dtype))	\
			 (__pair(first_dtype, second_dtype))), STL_DEFAULT_MAP_LINKED_CAPACITY); \
        STL_IF_ELSE_PTR_DTYPE(first_dtype)				\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__def_dmap_ptr_first_ptr_second(first_dtype, second_dtype)) \
	      (__def_dmap_ptr_first(first_dtype, second_dtype))) \
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__def_dmap_ptr_second(first_dtype)) \
	      (__def_dmap(first_dtype, second_dtype)))

#define __dmap(first_dtype, second_dtype)				\
	__stl_dmap_t_ ## first_dtype ## _ ## second_dtype
#define __dmap_ptr_first(one, first_dtype, second_dtype)	\
	__stl_dmap_t_ptr_ ## first_dtype ## _ ## second_dtype
#define __dmap_ptr_second(first_dtype, one, second_dtype)	\
	__stl_dmap_t_ ## first_dtype ## _ptr_ ## second_dtype
#define __dmap_ptr_first_ptr_second(one, first_dtype, one2, second_dtype) \
	__stl_dmap_t_ptr_ ## first_dtype ## _ptr_ ## second_dtype

#define dmap(first_dtype, second_dtype)				      \
	STL_IF_ELSE_PTR_DTYPE(first_dtype)				\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__dmap_ptr_first_ptr_second(first_dtype, second_dtype))	\
	      (__dmap_ptr_first(first_dtype, second_dtype)))		\
	     (STL_IF_ELSE_PTR_DTYPE(second_dtype)			\
	      (__dmap_ptr_second(first_dtype, second_dtype))	      \
	      (__dmap(first_dtype, second_dtype)))


#endif
