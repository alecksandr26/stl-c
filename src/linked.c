#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

#include "../include/stl/linked.h"
#include "../include/stl/gen.h"
#include "../include/stl/except.h"
#include "../include/stl/iter.h"

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

unsigned char *__stl_linked_ins_after_byindex(__stl_linked_t *linked, int index)
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
		linked->links = (__stl_link_node_t *) stl_realloc_container((unsigned char *) linked->links,
									    st_capacity(*linked)
									    * sizeof(__stl_con_t));
	}
	
	__stl_link_node_t *links;
	int curr;
	links = linked->links;

	if (linked->deleted_head == -1) {
		curr = st_size(*linked);
	} else {
		curr = linked->deleted_head;
		linked->deleted_head = links[curr].next;
	}

	links[curr].next = links[curr].prev = -1;
	if (st_size(*linked) != 0) {
		links[curr].prev = index;
		if (links[index].next != -1) {
			int next = links[index].next;
			links[next].prev = curr;
			links[curr].next = next;
		}
		links[index].next = curr;
	} else
		linked->front = linked->back = 0;

	if (links[curr].next == -1)
		linked->back = st_size(*linked);
	
	st_size(*linked)++;
	return linked->con.addr + (curr * linked->con.dtype_size);
}


unsigned char *__stl_linked_ins_prev_byindex(__stl_linked_t *linked, int index)
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
		linked->links = (__stl_link_node_t *) stl_realloc_container((unsigned char *) linked->links,
									    st_capacity(*linked)
									    * sizeof(__stl_con_t));
	}
	
	__stl_link_node_t *links;
	int curr;

	links = linked->links;
	if (linked->deleted_head == -1) {
		curr = st_size(*linked);
	} else {
		curr = linked->deleted_head;
		linked->deleted_head = links[curr].next;
	}

	links[curr].next = links[curr].prev = -1;
	if (st_size(*linked) != 0) {
		links[curr].next = index;
		if (links[index].prev != -1 ) {
			int prev;
			links[curr].prev = links[index].prev;
			prev = links[index].prev;
			links[prev].next = curr;
		}
		links[index].prev = curr;
	} else
		linked->front = linked->back = 0;

	if (links[curr].prev == -1)
		linked->front = st_size(*linked);
	
	st_size(*linked)++;
	return linked->con.addr + (curr * linked->con.dtype_size);
}

unsigned char *__stl_linked_rem_byindex(__stl_linked_t *linked, size_t curr)
{
	assert(linked != NULL);

	if (st_capacity(*linked) <= curr)
		throw(InvalidIndex);
	
	if (linked->con.type == STL_DYNAMIC
	    && st_size(*linked) <= st_capacity(*linked) / STL_DEFAULT_DLINKED_INCREASE_RATE) {
		linked->con.addr = linked->con.container =
			stl_realloc_container(linked->con.addr,
					      ((st_capacity(*linked)
						/  STL_DEFAULT_DLINKED_INCREASE_RATE) + 1)
					      * linked->con.dtype_size);
		st_capacity(*linked) = st_capacity(*linked) / STL_DEFAULT_DLINKED_INCREASE_RATE + 1;
		linked->links = (__stl_link_node_t *) stl_realloc_container((unsigned char *) linked->links,
									    st_capacity(*linked)
									    * sizeof(__stl_con_t));
	}

	__stl_link_node_t *links;
	int next, prev;
	links = linked->links;

	next = links[curr].next;
	prev = links[curr].prev;
	
	if (next != -1) {
		links[next].prev = links[curr].prev;
		if (curr == (size_t) linked->front)
			linked->front = next;
	}

	if (prev != -1) {
		links[prev].next = links[curr].next;
		if (curr == (size_t) linked->back)
			linked->back = prev;
	}
	
	links[curr].next = linked->deleted_head;
	linked->deleted_head= curr;

	st_size(*linked)--;
	return linked->con.addr + (curr * linked->con.dtype_size);
}

size_t __stl_linked_at(__stl_linked_t *linked, size_t index)
{
	assert(linked != NULL);

	if (st_empty(*linked))
		throw(EmptyStructure);

	if (st_size(*linked) <= index)
		throw(InvalidIndex);


	__stl_iter_t back, front;
	linked_begin(*linked, front);
	linked_end(*linked, back);
	
	while (iter_index(front) != (int) index && iter_index(back) != (int) index) {
		iter_next(front);
		iter_prev(back);
	}

	return (size_t) (iter_index(front) == (int) index) ? front.pos : back.pos;
}

void __stl_linked_begin(__stl_linked_t *linked, __stl_iter_t *iter)
{
	assert(linked != NULL);
	assert(iter != NULL);
	
	iter->st = (unsigned char *) linked;
	iter->pos = linked->front;
	iter->type = STL_ITERATING_LINKED;
	iter->index = 0;
}

void __stl_linked_end(__stl_linked_t *linked, __stl_iter_t *iter)
{
	assert(linked != NULL);
	assert(iter != NULL);

	iter->st = (unsigned char *) linked;
	iter->pos = linked->back;
	iter->type = STL_ITERATING_LINKED;
	iter->index = st_size(*linked) - 1;
}


int __stl_linked_find(__stl_linked_t *linked,
		      int memcmp(unsigned char *item1, unsigned char *item2, size_t item_size),
		      unsigned char *item)
{
	assert(linked != NULL);

	__stl_iter_t back, front;
	linked_begin(*linked, front);
	linked_end(*linked, back);
	
	while (iter_index(front) <= iter_index(back)) {
		if (memcmp(__stl_iter_data(&front), item, linked->con.dtype_size) == 0)
			return iter_index(front);
		iter_next(front);
		if (memcmp(__stl_iter_data(&back), item, linked->con.dtype_size) == 0)
			return iter_index(back);
		iter_prev(back);
	}
	
	return -1;
}



