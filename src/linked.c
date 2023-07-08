
#include <assert.h>
#include "../include/stl/linked.h"
#include "../include/stl/gen.h"
#include "../include/stl/ex.h"

size_t __stl_linked_front(__stl_linked_t *linked)
{
	assert(linked != NULL);

	if (st_empty(*linked))
		throw(EmptyStructure);

	return linked->front;
}

size_t __stl_linked_back(__stl_linked_t *linked)
{
	assert(linked != NULL);
	
	if (st_empty(*linked))
		throw(EmptyStructure);
	
	return linked->back;
}

__stl_link_node_t *__stl_linked_ins_after_byindex(__stl_linked_t *linked, int index)
{
	assert(linked != NULL);

	if ((int) st_size(*linked) < index)
		throw(InvalidIndex);

	if (st_size(*linked) + 1 == st_capacity(*linked)) {
		if (linked->con.type == STL_STATIC)
			throw(NotEnoughCapacity);
	}
	
	__stl_link_node_t *curr;

	curr = (__stl_link_node_t *) (linked->con.addr + (st_size(*linked) * linked->con.dtype_size));
	curr->prev = curr->next = NULL;
	if (index != -1) {	/* Link prev */
		curr->prev = (__stl_link_node_t *) (linked->con.addr + (index * linked->con.dtype_size));
		curr->next = curr->prev->next;
		curr->prev->next = curr;
	}

	if (curr->next == NULL)
		linked->back = st_size(*linked);
	
	st_size(*linked)++;
	return curr;
}


__stl_link_node_t *__stl_linked_ins_prev_byindex(__stl_linked_t *linked, int index)
{
	assert(linked != NULL);

	if ((int) st_size(*linked) < index)
		throw(InvalidIndex);

	if (st_size(*linked) + 1 == st_capacity(*linked)) {
		if (linked->con.type == STL_STATIC)
			throw(NotEnoughCapacity);
	}
	
	__stl_link_node_t *curr;

	curr = (__stl_link_node_t *) (linked->con.addr + (st_size(*linked) * linked->con.dtype_size));
	curr->prev = curr->next = NULL;
	if (index != -1) {	/* Link prev */
		curr->next = (__stl_link_node_t *) (linked->con.addr + (index * linked->con.dtype_size));
		curr->prev = curr->next->prev;
		curr->next->prev = curr;
	}

	if (curr->prev == NULL)
		linked->front = st_size(*linked);
	
	st_size(*linked)++;
	return curr;
}

__stl_link_node_t *__stl_linked_rem_byindex(__stl_linked_t *linked, size_t index)
{
	assert(linked != NULL);

	if (st_size(*linked) < index)
		throw(InvalidIndex);

	__stl_link_node_t *curr, *next, *prev;
	curr = (__stl_link_node_t *) (linked->con.addr + (index * linked->con.dtype_size));

	next = curr->next;
	prev = curr->prev;

	if (next) {
		next->prev = curr->prev;
		if (index == linked->front)
			linked->front = (size_t )((unsigned char *) next - linked->con.addr)
				/ linked->con.dtype_size;
	}

	if (prev) {
		prev->next = curr->next;
		curr->prev = NULL;
		if (index == linked->back)
			linked->back = (size_t) ((unsigned char *) prev - linked->con.addr)
				/ linked->con.dtype_size;
	}

	/* Link the deleted cells */
	curr->next = linked->deleted_head;
	linked->deleted_head = curr;

	st_size(*linked)--;
	
	return curr;
}


