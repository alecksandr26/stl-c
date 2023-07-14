#ifndef INIT_INCLUDED
#define INIT_INCLUDED

typedef enum {__STL_STACK_TYPE} __stl_stack_type;
typedef enum {__STL_QUEUE_TYPE} __stl_queue_type;
typedef enum {__STL_ARRAY_TYPE} __stl_array_type;
typedef enum {__STL_LINKED_TYPE} __stl_linked_type;
typedef enum {__STL_MAP_TYPE} __stl_map_type;

#define __stl_initialize_st(st)						\
	_Generic(((st).type),						\
		 __stl_linked_type : __stl_initialize_linked((unsigned char *) &st), \
		 __stl_queue_type : __stl_initialize_queue((unsigned char *) &st),		\
		 __stl_map_type : __stl_initialize_map((unsigned char *) &st), \
		 default: (void) 0)

#define __stl_destroy_st(st)						\
	_Generic(((st).type),						\
		 __stl_linked_type : __stl_destroy_linked((unsigned char *) &st),		\
		 default: (void) 0)

extern void __stl_initialize_linked(unsigned char *st);
extern void __stl_initialize_queue(unsigned char *st);
extern void __stl_initialize_map(unsigned char *st);

extern void __stl_destroy_linked(unsigned char *st);

#endif
