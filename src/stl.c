#include <tc.h>
#include <assert.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>

#include "../include/stl/init.h"
#include "../include/stl/linked.h"
#include "../include/stl/queue.h"
#include "../include/stl/map.h"
#include "../include/stl/gen.h"
#include "../include/stl/con.h"
#include "../include/stl/except.h"

Except NotEnoughCapacity = {"NotEnoughCapacity: Not enough capacity in the structure"};
Except EmptyStructure = {"EmptyStructure: The structure is empty, it doesn't have any element"};
Except NotEnoughMemory = {"NotEnoughMemory: Not enough memory for a new structure allocation"};
Except NotEnoughMemoryToRealloc =					\
	{"NotEnoughMemoryToRealloc: Not enough memory for a reallocation of the container"};
Except InvalidIndex = {"InvalidIndex: Recived an invalid index"};
Except CapacityAlreadyInitialized = {"CapacityAlreadyInitialized: Capacity already initialized"};
Except InvalidKey = {"InvalidKey: Invalid key for the structure"};
Except UninitializedIter = {"UninitializedIter: Uninitialized iterator"};
Except LastElementReached = {"LastElementReached: Last element reached"};
Except PointingToNullValue = {"PointingToNullValue: Pointing to null value"};
Except KeyNotFound = {"KeyNotFound: Key not found"};
Except KeyAlreadyExist = {"KeyAlreadyExist: Key already exist"};

int stl_memcmp(unsigned char *item1, unsigned char *item2, size_t item_size)
{
	assert(item1 != NULL);
	assert(item2 != NULL);
	assert(item_size > 0);

	for (size_t i = 0; i < item_size; i++) {
		int cmp = item2[i] - item1[i];
		if (cmp)
			return cmp;
	}

	return 0;
}

unsigned long stl_heapaddr = 0;

unsigned char *stl_alloc_struct(size_t st_size)
{
	unsigned char *st_ptr;
	
	if ((st_ptr = malloc(st_size)) == NULL)
		throw(NotEnoughMemory);

	if (stl_heapaddr < (unsigned long) st_ptr)
		stl_heapaddr = ((unsigned long) st_ptr) + st_size;

	return st_ptr;
}

unsigned char *stl_alloc_container(size_t container_capacity)
{
	unsigned char *container;

	if ((container = malloc(container_capacity)) == NULL)
		throw(NotEnoughMemory);

	if (stl_heapaddr < (unsigned long) container)
		stl_heapaddr = ((unsigned long) container) + container_capacity;

	return container;
}

unsigned char *stl_realloc_container(unsigned char *container_ptr, size_t new_container_capacity)
{
	assert(container_ptr != NULL);

	if ((container_ptr = realloc(container_ptr, new_container_capacity)) == NULL)
		throw(NotEnoughMemoryToRealloc);

	if (stl_heapaddr < (unsigned long) container_ptr)
		stl_heapaddr = ((unsigned long) container_ptr) + new_container_capacity;

	return container_ptr;
}

void stl_free_container(unsigned char *container_ptr, size_t container_capacity)
{
	assert(container_ptr != NULL);
	
	if (stl_heapaddr == ((unsigned long) container_ptr) + container_capacity)
		stl_heapaddr = ((unsigned long) container_ptr);

	free(container_ptr);
}

void stl_free_struct(unsigned char *st_ptr)
{
	assert(st_ptr != NULL);
	
	free(st_ptr);
}

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
		l->con.dtype_size = ((m->con.dtype_size - sizeof(__stl_linked_t)
				      + sizeof(void *) - sizeof(__stl_link_node_t)
				      * STL_DEFAULT_MAP_LINKED_CAPACITY)
				     / STL_DEFAULT_MAP_LINKED_CAPACITY);
		l->con.addr = (unsigned char *) l + (sizeof(__stl_linked_t) - sizeof(void *));
		__stl_initialize_linked((unsigned char *) l);
	}
}
