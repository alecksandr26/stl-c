#include <stddef.h>
#include <assert.h>
#include <except.h>
#include <string.h>
#include <stdio.h>

#include "../include/stl/list.h"
#include "../include/stl/ex.h"

static int bs_array(unsigned char *arr, void *new_ele, size_t size, size_t isize,
		       int (cmp)(void *i1, void *i2))
{
	assert(arr != NULL
	       && cmp != NULL
	       && new_ele != NULL
	       && "None of them shuld be null");
	assert(isize > 0 && "The size of one element can't be zero");

	int l = 0, r = (int) size, m = 0, cmpr = 0;

	while (r > l) {
		m = (r - l) / 2 + l;
		cmpr = cmp(&arr[m * isize], new_ele);
		/* cmpr = -INT_MAX -> arr[m] > new_ele
		   cmpr = 0 -> arr[m] = new_ele
		   cmpr = INT_MAX -> arr[m] < new_ele
		 */
		if (cmpr == 0)
			break;
		else if (cmpr > 0)
			l = ++m;
		else
			r = --m;
	}

	return m;
}


static size_t comp_pind(__stl_list_t *list, size_t lind)
{
	size_t j = 0;

	/* Try to swap elements from the container, uelems */

	while (j < list->size_ul && lind + j >= list->uelems[j].pind) {
		if (list->uelems[j].lind == (int) lind)
			return list->uelems[j].pind;
		j++;
	}

	return lind + j;
}

static size_t uelems_cmp(__stl_unorderedlist_t *uelem1, __stl_unorderedlist_t *uelem2)
{
	return (int) uelem2->pind - (int) uelem1->pind;
}


static __stl_linkedlist_t *comp_head(__stl_list_t *list)
{
	if (list->size == 0)
		return NULL;

	__stl_linkedlist_t *head;

	for (head = &list->linked[list->size_con - 1];
	     head->next != NULL;
	     head = head->next);
	return head;
}


size_t list_insert_byindex(__stl_list_t *list, size_t ind)
{
	assert(list != NULL && "Can't be null");

	if (list_size(*list) < ind && !list_empty(*list))
		throw_except(InvalidIndex);

	size_t cindex, cindex_tins;
	__stl_linkedlist_t *next, *prev;

	cindex_tins = comp_pind(list, ind);
	if (stack_size(*list->st) > 0) {
		cindex = stack_pop(*list->st);
		
		__stl_unorderedlist_t uelem = {
			.lind = ind,
			.pind = cindex,
			.cpos = (ind > cindex) ? STL_LIST_RIGHT : STL_LIST_LEFT
		};

		int m = bs_array((unsigned char *) list->uelems, &uelem, list->size_ul,
				 sizeof(__stl_unorderedlist_t),
				 (int (*)(void *, void *)) uelems_cmp);

		list->uelems[m].lind = ind;
	} else
		cindex = list->size_con;

	if (cindex_tins >= list->size_con) {
		prev = comp_head(list);
		next = NULL;
	} else {
		prev = &list->linked[cindex_tins];
		next = list->linked[cindex_tins].next;

		
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

	list->linked[cindex].pind = cindex;
	list->size++;
	if (list->size_con == cindex)
		list->size_con++;
	return cindex;
}


size_t list_inc(__stl_list_t *list)
{
	assert(list != NULL && "Can't be null");
	return list_insert_byindex(list, list->size);
}

size_t list_fetch_byindex(__stl_list_t *list, size_t ind)
{
	assert(list != NULL && "Can't be null");

	if (list_size(*list) <= ind)
		throw_except(InvalidIndex);

	return comp_pind(list, ind);
}

size_t list_remove_byindex(__stl_list_t *list, size_t ind)
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
		__stl_unorderedlist_t uelem = {
			.pind = cindex,
			.lind = - 1,
			.cpos = STL_LIST_NONE
		};

		/* Solve the problem of the logical index afected by the erase of the other element
		   ideas: Creating a linkedlist of unordered elements, iterate the whole list 
		 */
		
		int m = bs_array((unsigned char *) list->uelems, &uelem, list->size_ul,
				 sizeof(__stl_unorderedlist_t),
				 (int (*)(void *, void *)) uelems_cmp);
		if ((int) list->size_ul > m && list->uelems[m].pind == cindex) {
			list->uelems[m].lind = -1;
			list->uelems[m].cpos = STL_LIST_NONE;
		} else {
			for (int i = list->size_ul; i > m; i--)
				memcpy(&list->uelems[i], &list->uelems[i - 1], sizeof(__stl_unorderedlist_t));
			memcpy(&list->uelems[m], &uelem, sizeof(__stl_unorderedlist_t));
			list->size_ul++;
		}
		
		stack_push(*list->st, cindex);
	}
	
	list->size--;
	return cindex;
}

size_t list_dec(__stl_list_t *list)
{
	assert(list != NULL && "Can't be null");
	
	return list_remove_byindex(list, list->size_con - 1);
}
