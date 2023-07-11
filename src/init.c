#include <assert.h>

#include "../include/stl/linked.h"
#include "../include/stl/queue.h"
#include "../include/stl/gen.h"


void __stl_initialize_linked(void *st)
{
	assert(st != NULL);
	
	__stl_linked_t *linked = (__stl_linked_t *) st;

	linked->deleted_head = linked->back = linked->front = -1;
}

void __stl_initialize_stack(void *st)
{
	assert(st != NULL);
}

void __stl_initialize_queue(void *st)
{
	assert(st != NULL);
	__stl_queue_t *queue = st;

	queue->front = queue->rear = 0;
}

void __stl_initialize_array(void *st)
{
	assert(st != NULL);
}

void __stl_initialize_map(void *st)
{
	assert(st != NULL);
}

