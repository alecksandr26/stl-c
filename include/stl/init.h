#ifndef INIT_INCLUDED
#define INIT_INCLUDED

typedef enum {__STL_STACK_TYPE} __stl_stack_type;
typedef enum {__STL_QUEUE_TYPE} __stl_queue_type;
typedef enum {__STL_ARRAY_TYPE} __stl_array_type;
typedef enum {__STL_LINKED_TYPE} __stl_linked_type;

#define __stl_initialize_st(st)						\
	_Generic(((st).type),						\
		 __stl_linked_type : __stl_initialize_linked,		\
		 __stl_stack_type : __stl_initialize_stack,		\
		 __stl_queue_type : __stl_initialize_queue,		\
		 __stl_array_type : __stl_initialize_array)((void *) &(st))

extern void __stl_initialize_linked(void *st);
extern void __stl_initialize_array(void *st);
extern void __stl_initialize_stack(void *st);
extern void __stl_initialize_queue(void *st);

#endif
