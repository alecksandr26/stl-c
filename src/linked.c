#include <stdio.h>
#include <assert.h>

#include "../include/stl/linked.h"
#include "../include/stl/gen.h"
#include "../include/stl/ex.h"

size_t __stl_linked_front(__stl_linked_t *linked)
{
	assert(linked != NULL);

	if (st_empty(*linked))
		throw(EmptyStructure);

	return (size_t) linked->front;
}

size_t __stl_linked_back(__stl_linked_t *linked)
{
	assert(linked != NULL);
	
	if (st_empty(*linked))
		throw(EmptyStructure);
	
	return (size_t) linked->back;
}

__stl_link_node_t *__stl_linked_ins_after_byindex(__stl_linked_t *linked, int index)
{
	assert(linked != NULL);

	if ((int) st_size(*linked) < index)
		throw(InvalidIndex);
	
	if (st_size(*linked) == st_capacity(*linked)) {
		if (linked->con.type == STL_STATIC)
			throw(NotEnoughCapacity);
		linked->con.addr = linked->con.container =
			stl_realloc_container(linked->con.addr,
					      st_capacity(*linked)
					      * STL_DEFAULT_DLINKED_INCREASE_RATE
					      * linked->con.dtype_size);
		st_capacity(*linked) = st_capacity(*linked) * STL_DEFAULT_DLINKED_INCREASE_RATE;
	}
	
	__stl_link_node_t *curr, *ins_addr, *addr_next;;
	int curr_index;

	if (linked->deleted_head == -1) {
		curr_index = st_size(*linked);
	} else {
		curr_index = linked->deleted_head;
		linked->deleted_head = ((__stl_link_node_t *) (linked->con.addr
							       + (curr_index * linked->con.dtype_size)))->next;
	}

	curr = (__stl_link_node_t *) (linked->con.addr + (curr_index * linked->con.dtype_size));

	curr->prev = curr->next = -1;
	if (index != -1) {	/* Link prev */
		ins_addr = (__stl_link_node_t *) (linked->con.addr
						  + (index * linked->con.dtype_size));
		curr->prev = index;
		if (ins_addr->next != -1) {
			addr_next = (__stl_link_node_t *) (linked->con.addr
							   + (ins_addr->next * linked->con.dtype_size));
			addr_next->prev = curr_index;
			curr->next = ins_addr->next;
		}
		ins_addr->next = curr_index;
	} else
		linked->front = linked->back = 0;

	if (curr->next == -1)
		linked->back = st_size(*linked);
	
	st_size(*linked)++;
	return curr;
}


__stl_link_node_t *__stl_linked_ins_prev_byindex(__stl_linked_t *linked, int index)
{
	assert(linked != NULL);

	if ((int) st_size(*linked) < index)
		throw(InvalidIndex);

	if (st_size(*linked) == st_capacity(*linked)) {
		if (linked->con.type == STL_STATIC)
			throw(NotEnoughCapacity);
		linked->con.addr = linked->con.container =
			stl_realloc_container(linked->con.addr,
					      st_capacity(*linked)
					      * STL_DEFAULT_DLINKED_INCREASE_RATE
					      * linked->con.dtype_size);
		st_capacity(*linked) = st_capacity(*linked) * STL_DEFAULT_DLINKED_INCREASE_RATE;
	}
	
	__stl_link_node_t *curr, *ins_addr, *addr_prev;
	int curr_index;

	if (linked->deleted_head == -1) {
		curr_index = st_size(*linked);
	} else {
		curr_index = linked->deleted_head;
		linked->deleted_head = ((__stl_link_node_t *) (linked->con.addr
							       + (curr_index * linked->con.dtype_size)))->next;
	}

	curr = (__stl_link_node_t *) (linked->con.addr + (curr_index * linked->con.dtype_size));
	
	curr->prev = curr->next = -1;
	if (index != -1) {	/* Link prev */
		ins_addr = (__stl_link_node_t *) (linked->con.addr + (index * linked->con.dtype_size));
		curr->next = index;
		if (ins_addr->prev != -1 ) {
			curr->prev = ins_addr->prev;
			addr_prev = (__stl_link_node_t *) (linked->con.addr
							   + (ins_addr->prev * linked->con.dtype_size));
			addr_prev->next = curr_index;
		}
		ins_addr->prev = curr_index;
	} else
		linked->front = linked->back = 0;

	if (curr->prev == -1)
		linked->front = st_size(*linked);
	
	st_size(*linked)++;
	return curr;
}

__stl_link_node_t *__stl_linked_rem_byindex(__stl_linked_t *linked, size_t physical_index)
{
	assert(linked != NULL);

	if (st_capacity(*linked) <= physical_index)
		throw(InvalidIndex);
	
	if (linked->con.type == STL_DYNAMIC
	    && st_size(*linked) <= st_capacity(*linked) / STL_DEFAULT_DLINKED_INCREASE_RATE) {
		linked->con.addr = linked->con.container =
			stl_realloc_container(linked->con.addr,
					      ((st_capacity(*linked)
						/  STL_DEFAULT_DLINKED_INCREASE_RATE) + 1)
					      * linked->con.dtype_size);
		st_capacity(*linked) = st_capacity(*linked) / STL_DEFAULT_DLINKED_INCREASE_RATE + 1;
	}

	__stl_link_node_t *curr;
	int next_index, prev_index;
	curr = (__stl_link_node_t *) (linked->con.addr + (physical_index * linked->con.dtype_size));

	next_index = curr->next;
	prev_index = curr->prev;
	
	if (next_index != -1) {
		__stl_link_node_t *next = (__stl_link_node_t *) (linked->con.addr
								 + (next_index * linked->con.dtype_size));
		next->prev = curr->prev;
		if (physical_index == (size_t) linked->front)
			linked->front = next_index;
	}

	if (prev_index != -1) {
		__stl_link_node_t *prev = (__stl_link_node_t *) (linked->con.addr
								 + (prev_index * linked->con.dtype_size));
		prev->next = curr->next;
		if (physical_index == (size_t) linked->back)
			linked->back = prev_index;
	}

	/* Link the deleted cells */
	curr->next = linked->deleted_head;
	linked->deleted_head = physical_index;

	st_size(*linked)--;
	return curr;
}

size_t __stl_linked_at(__stl_linked_t *linked, size_t index)
{
	assert(linked != NULL);

	if (st_empty(*linked))
		throw(EmptyStructure);

	if (st_size(*linked) <= index)
		throw(InvalidIndex);

	size_t c1, c2;
	int front, back;
	front = linked->front;
	back = linked->back;
	
	c1 = 0;
	c2 = st_size(*linked) - 1;
	while (c1 != index && c2 != index) {
		front = ((__stl_link_node_t *) (linked->con.addr + (front * linked->con.dtype_size)))->next;
		back = ((__stl_link_node_t *) (linked->con.addr + (back * linked->con.dtype_size)))->prev;
		c1++;
		c2--;
	}

	return (c1 == index) ? front : back;
}


