#include <stddef.h>
#include <assert.h>
#include <tc.h>
#include <string.h>
#include <stdio.h>

#include "../include/stl/list.h"
#include "../include/stl/gen.h"
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

static __stl_linkedlist_t *comp_head(__stl_list_t *list, size_t n)
{
	assert(list != NULL);
	
	if (st_size(*list) == 0)
		return NULL;

	__stl_linkedlist_t *head;

	for (head = &list->linked[n - 1];
	     head->next != NULL;
	     head = head->next);
	return head;
}

static void add_unorderd_elem(__stl_list_t *list, __stl_unorderedlist_t *uelem)
{
	assert(uelem != NULL && list != NULL);
	size_t m = 0;
	
	for (size_t i = 0; i < list->size_ul; i++) {
		if (list->uelems[i].pind < uelem->pind)
			m++;
		if (uelem->lind != -1 && list->uelems[i].lind != -1) {
			if (uelem->lind <= list->uelems[i].lind)
				list->uelems[i].lind++;
		}
	}
	
	if (m >= list->size_ul)
		list->size_ul++;

	memcpy(&list->uelems[m], uelem, sizeof(__stl_unorderedlist_t));
}

static void move_cell(__stl_list_t *list, size_t pind, size_t new_pind)
{
	assert(list != NULL && "Can't be null");

	/* First update the linked array */
	__stl_linkedlist_t *next = list->linked[pind].next,
		*prev = list->linked[pind].prev;

	if (prev) {
		prev->next = &(list->linked[new_pind]);
		list->linked[new_pind].prev = prev;
	} else
		list->linked[new_pind].prev = NULL;
	
	if (next) {
		next->prev = &(list->linked[new_pind]);
		list->linked[new_pind].next = next;
	} else
		list->linked[new_pind].next = NULL;

	memcpy((unsigned char *) list->container + (new_pind * list->con.dtype_size),
	       (unsigned char *) list->container + (pind * list->con.dtype_size),
	       list->con.dtype_size);
}


size_t list_insert_byindex(__stl_list_t *list, size_t ind)
{
	assert(list != NULL && "Can't be null");

	if (list_size(*list) < ind && !list_empty(*list))
		throw(InvalidIndex);

	size_t cindex, cindex_tins;
	__stl_linkedlist_t *next, *prev;

	cindex_tins = comp_pind(list, ind);
	if (stack_size(*list->st) > 0) {
		/* TODO: Try to optimize this decision, instead of an stack try to do a better selection
		   Also think in the posibility that the logical index is the same as the physical
		*/
		cindex = stack_pop(*list->st);
	} else
		cindex = list->size_con++;

	if (cindex_tins != cindex) {
		/* Bug here at the linked list */

		__stl_unorderedlist_t uelem = {
			.lind = ind,
			.pind = cindex
		};
		
		prev = list->linked[cindex_tins].prev;
		next = &list->linked[cindex];   /* Here is the bug */
		
		if (ind < list->size) {
			/* Move the cell */
			move_cell(list, cindex_tins, cindex);
			list->linked[cindex].prev = &list->linked[cindex_tins];
			cindex = cindex_tins;
			uelem.lind = ind + 1;
		} else
			next = NULL;	     /* Inserting to the end */
		
		add_unorderd_elem(list, &uelem);
	} else {
		prev = comp_head(list, list->size_con - 1);
		next = NULL;
	}

	/* Link the elements */
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
	return cindex;
}

size_t list_fetch_byindex(__stl_list_t *list, size_t ind)
{
	assert(list != NULL && "Can't be null");

	if (st_size(*list) <= ind)
		throw(InvalidIndex);

	return comp_pind(list, ind);
}

size_t list_remove_byindex(__stl_list_t *list, size_t ind)
{
	assert(list != NULL && "Can't be null");

	if (list_empty(*list))
		throw(EmptyStructure);

	if (list_size(*list) <= ind)
		throw(InvalidIndex);
	
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
