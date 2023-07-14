
#include <assert.h>
#include <stdio.h>
#include "../include/stl/init.h"
#include "../include/stl/linked.h"
#include "../include/stl/queue.h"
#include "../include/stl/map.h"
#include "../include/stl/gen.h"

void __stl_initialize_linked(unsigned char *st)
{
	assert(st != NULL);
	
	__stl_linked_t *l = (__stl_linked_t *) st;
	l->deleted_head = l->back = l->front = -1;
	if (l->con.type == STL_DYNAMIC) {
		l->links = (__stl_link_node_t *) stl_alloc_container(st_capacity(*l)
								     * sizeof(__stl_link_node_t));
	} else {
		l->links = (__stl_link_node_t *) ((unsigned char *) &l->con
						  + (sizeof(__stl_con_t) - sizeof(void *))
						  + st_capacity(*l) * l->con.dtype_size);
	}
	
}

void __stl_destroy_linked(unsigned char *st)
{
	assert(st != NULL);
	__stl_linked_t *l = (__stl_linked_t *) st;
	if (l->con.type == STL_DYNAMIC)
		stl_free_container((unsigned char *) l->links, st_capacity(*l) * sizeof(__stl_con_t));
}

void __stl_initialize_queue(unsigned char *st)
{
	assert(st != NULL);

	__stl_queue_t *q = (__stl_queue_t *) st;
	q->front = q->rear = 0;
}

void __stl_initialize_map(unsigned char *st)
{
	assert(st != NULL);
	__stl_map_t *m = (__stl_map_t *) st;
	for (size_t i = 0; i < m->con.capacity; i++) {
		__stl_linked_t *l = (__stl_linked_t *) (m->con.addr + i * m->con.dtype_size);
		l->con.size = 0;
		l->con.type = STL_STATIC;
		l->con.capacity = STL_DEFAULT_MAP_LINKED_CAPACITY;
		l->con.st_size = m->con.dtype_size;
		l->con.dtype_size = ((m->con.dtype_size - sizeof(__stl_linked_t) + sizeof(void *))
				     / STL_DEFAULT_MAP_LINKED_CAPACITY);
		l->con.addr = (unsigned char *) l + (sizeof(__stl_linked_t) - sizeof(void *));
		__stl_initialize_linked((unsigned char *) l);
	}
}
