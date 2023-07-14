
#include <assert.h>
#include <tc.h>

#include "../include/stl/iter.h"
#include "../include/stl/ex.h"
#include "../include/stl/linked.h"
#include "../include/stl/array.h"
#include "../include/stl/gen.h"

void __stl_iter_next(__stl_iter_t *iter)
{
	assert(iter != NULL);
	__stl_linked_t *l;
	__stl_link_node_t *links;
	__stl_array_t *a;
	
	switch ((int) iter->type) {
	case STL_ITERATING_ARRAY:
		a = (__stl_array_t *) iter->st;
		if (iter->pos < 0 || iter->pos >= (int) st_size(*a))
			throw(LastElementReached);
		iter->pos++;
		iter->index++;
		break;
	case STL_ITERATING_LINKED:
		if (iter->pos == -1)
			throw(LastElementReached);
		
		l = (__stl_linked_t *) iter->st;
		links = l->links;
		iter->pos = links[iter->pos].next;
		iter->index++;
		break;
	default:
		throw(UninitializedIter);
	}
}

void __stl_iter_prev(__stl_iter_t *iter)
{
	assert(iter != NULL);
	__stl_link_node_t *links;
	__stl_linked_t *l;
	__stl_array_t *a;

	if (iter->type > STL_ITERATING_LINKED || iter->type == STL_ITERATING_NONE)
		throw(UninitializedIter);

	switch ((int) iter->type) {
	case STL_ITERATING_ARRAY:
		a = (__stl_array_t *) iter->st;
		if (iter->pos < 0 || iter->pos >= (int) st_size(*a))
			throw(LastElementReached);
		iter->pos--;
		iter->index--;
		break;
	case STL_ITERATING_LINKED:
		if (iter->pos == -1)
			throw(LastElementReached);
		
		l = (__stl_linked_t *) iter->st;
		links = l->links;
		iter->pos = links[iter->pos].prev;
		iter->index--;
		break;
	default:
		throw(UninitializedIter);
	}
}

unsigned char *__stl_iter_data(__stl_iter_t *iter)
{
	assert(iter != NULL);
	__stl_linked_t *l;
	__stl_array_t *a;

	if (iter->type > STL_ITERATING_LINKED || iter->type == STL_ITERATING_NONE)
		throw(UninitializedIter);

	switch ((int) iter->type) {
	case STL_ITERATING_ARRAY:
		a = (__stl_array_t *) iter->st;
		if (iter->pos < 0 || iter->pos >= (int) st_size(*a))
			throw(PointingToNullValue);
		return a->con.addr + (iter->pos * a->con.dtype_size);
		break;
	case STL_ITERATING_LINKED:
		if (iter->pos == -1)
			throw(PointingToNullValue);
		
		l = (__stl_linked_t *) iter->st;

		if (iter->index < 0 || iter->index >= (int) st_size(*l))
			throw(PointingToNullValue);
		
		return l->con.addr + (iter->pos * l->con.dtype_size);
		break;
	default:
		throw(UninitializedIter);
	}

	assert(0);
	return NULL;
}


