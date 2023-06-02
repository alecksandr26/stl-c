#include <stddef.h>
#include <assert.h>
#include <except.h>
#include <string.h>
#include <stdio.h>

#include "../include/stl/list.h"
#include "../include/stl/ex.h"

static size_t comp_pind(__stl_list_t *list, size_t lind)
{
	int j = 0;

	/* made the logical decrementation */
	for (size_t c = 0; c < list->size_ul; c++) {
		if (list->uelems[c].lind == (int) lind)
			return list->uelems[c].pind;
		else if (list->uelems[c].lind < (int) lind && list->uelems[c].lind != -1)
			if (lind <= list->uelems[c].pind)
				lind--;
	}

	
	for (size_t c = 0; c < list->size_ul; c++) {
		if (list->uelems[c].lind > (int) lind || list->uelems[c].lind == -1) {
			if (lind + j >= list->uelems[c].pind)
				j++;
		}
	}
	
	return lind + j;
}

static __stl_linkedlist_t *comp_head(__stl_list_t *list)
{
	assert(list != NULL);
	
	if (list->size == 0)
		return NULL;

	__stl_linkedlist_t *head;

	for (head = &list->linked[list->size_con - 1];
	     head->next != NULL;
	     head = head->next);
	return head;
}

static void add_unorderd_elem(__stl_list_t *list, __stl_unorderedlist_t *uelem)
{
	assert(uelem != NULL && list != NULL);
	size_t m = 0;
	
	/* TODO: Do a binary search here pls */
	for (size_t i = 0; i < list->size_ul; i++) {
		if (list->uelems[i].pind < uelem->pind)
			m++;
		if (uelem->lind != -1 && list->uelems[i].lind != -1) {
			if (uelem->lind < list->uelems[i].lind)
				list->uelems[i].lind++;
		}

	}
	
	if (m >= list->size_ul)
		list->size_ul++;

	memcpy(&list->uelems[m], uelem, sizeof(__stl_unorderedlist_t));
}


size_t list_insert_byindex(__stl_list_t *list, size_t ind, void *container)
{
	assert(list != NULL && "Can't be null");

	if (list_size(*list) < ind && !list_empty(*list))
		throw_except(InvalidIndex);

	size_t cindex, cindex_tins;
	__stl_linkedlist_t *next, *prev;

	cindex_tins = comp_pind(list, ind);
	if (stack_size(*list->st) > 0) {
		/* TODO: Try to optimize this decision instead of an stack try to do a better selection
		   Also think in the posibility that the logical index is the same as the physical
		 */
		cindex = stack_pop(*list->st);
	} else
		cindex = list->size_con;

	if (cindex_tins >= list->size_con) {
		prev = comp_head(list);
		next = NULL;
	} else {
		prev = list->linked[cindex_tins].prev;
		next = &list->linked[cindex_tins];
	}

	if (cindex_tins != cindex) {
		__stl_unorderedlist_t uelem = {
			.lind = ind,
			.pind = cindex
		};
		
		add_unorderd_elem(list, &uelem);
	}
	
	if (prev != NULL) {
		prev->next = &(list->linked[cindex]);
		list->linked[cindex].prev = prev;
	} else
		list->linked[cindex].prev = NULL;
	if (next != NULL) {
		next->prev = &(list->linked[cindex]);
		list->linked[cindex].next = next;
	} else
		list->linked[cindex].next = NULL;

	list->size++;
	if (list->size_con == cindex)
		list->size_con++;
	return cindex;
}

size_t list_fetch_byindex(__stl_list_t *list, size_t ind, void *container)
{
	assert(list != NULL && "Can't be null");

	if (list_size(*list) <= ind)
		throw_except(InvalidIndex);

	return comp_pind(list, ind);
}

size_t list_remove_byindex(__stl_list_t *list, size_t ind, void *container)
{
	assert(list != NULL && "Can't be null");

	if (list_empty(*list))
		throw_except(EmptyStructure);

	if (list_size(*list) <= ind)
		throw_except(InvalidIndex);
	
	const size_t cindex = comp_pind(list, ind);
	
	if (list->linked[cindex].prev)
		list->linked[cindex].prev->next = list->linked[cindex].next;
	if (list->linked[cindex].next)
		list->linked[cindex].next->prev = list->linked[cindex].prev;

	if (list->size_con - 1 == cindex) {
		list->size_con--;
	} else {
		/* Solve the problem of the logical index afected by the erase of the other element
		   ideas: Creating a linkedlist of unordered elements, iterate the whole list 
		 */
		__stl_unorderedlist_t uelem = {
			.lind = -1,
			.pind = cindex
		};

		add_unorderd_elem(list, &uelem);
		
		stack_push(*list->st, cindex);
	}
	
	list->size--;
	return cindex;
}
