#include <stdio.h>
#include "../include/stl/iter.h"
#include "../include/stl/pair.h"
#include "../include/stl/array.h"
#include "../include/stl/linked.h"
#include "../include/stl/gen.h"

int main(void)
{
	def_linked(int);
	linked(int) l;
	
	init_st(l);

	linked_push_back(l, 10);
	linked_push_back(l, 20);
	linked_push_back(l, 30);
	linked_push_back(l, 40);
	linked_push_back(l, 50);

	def_iter(linked(int));
	
	iter(linked(int)) iter;
	
	for (linked_begin(l, iter); iter_index(iter) < (int) st_size(l); iter_next(iter))
		printf("%i\n", iter_data(iter));
	
	for (linked_end(l, iter); iter_index(iter) >= 0; iter_prev(iter))
		printf("%i\n", iter_data(iter));

	
	/* Iterating the array */
	def_array(int);
	array(int) a;
	init_st(a);

	array_push(a, 10);
	array_push(a, 20);
	array_push(a, 30);
	array_push(a, 40);
	array_push(a, 50);

	def_iter(array(int));
	iter(array(int)) iter2;
	
	for (array_begin(a, iter2); iter_index(iter2) < (int) st_size(a); iter_next(iter2))
		printf("%i\n", iter_data(iter2));


	for (array_end(a, iter2); iter_index(iter2) >= 0; iter_prev(iter2))
		printf("%i\n", iter_data(iter2));



	array(int) *a_ptr = new_st(array(int));
	init_st(*a_ptr);

	array_push(*a_ptr, 10);
	array_push(*a_ptr, 20);
	array_push(*a_ptr, 30);
	array_push(*a_ptr, 40);
	array_push(*a_ptr, 50);

	iter(array(int)) iter3;
	
	for (array_begin(*a_ptr, iter3); iter_index(iter3) < (int) st_size(*a_ptr); iter_next(iter3))
		printf("%i\n", iter_data(iter3));


	for (array_end(*a_ptr, iter3); iter_index(iter3) >= 0; iter_prev(iter3))
		printf("%i\n", iter_data(iter3));
	
	stl_free(*a_ptr);
	
	return 0;
}



