

#ifndef ITER_INCLUDE
#define ITER_INCLUDE

#include <stddef.h>
#include "init.h"

typedef enum {
	STL_ITERATING_NONE = 0,
	STL_ITERATING_ARRAY,
	STL_ITERATING_LINKED
} ITERATING_STRUCTURE_TYPE;

typedef struct {
	unsigned char *st;
	int pos, index;
	ITERATING_STRUCTURE_TYPE type;
} __stl_iter_t;

#define __stl_def_iter(st_type)			\
	typedef struct {			\
		st_type *st;			\
		int pos, index;			\
		ITERATING_STRUCTURE_TYPE type;	\
	} __stl_iter_t_ ## st_type

#define def_iter(st_type)			\
	__stl_def_iter(st_type)

#define __stl_iter(st)				\
	__stl_iter_t_ ## st

#define iter(st)				\
	__stl_iter(st)				\

#define iter_next(iter)				\
	__stl_iter_next((__stl_iter_t *) &(iter))
#define iter_prev(iter)					\
	__stl_iter_prev((__stl_iter_t *) &(iter))

#define iter_data(iter)				\
	*((typeof((iter).st->con.container[0]) *) __stl_iter_data((__stl_iter_t *) &(iter)))

#define iter_index(iter)			\
	(iter).index

extern void __stl_iter_next(__stl_iter_t *iter);
extern void __stl_iter_prev(__stl_iter_t *iter);
extern unsigned char *__stl_iter_data(__stl_iter_t *iter);

#endif

