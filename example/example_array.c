
#include <stdio.h>

#include "../include/stl/array.h"
#include "../include/stl/gen.h"

int main(void)
{
	puts("Static structure");
	def_array(int);
	array(int) arr;
	init_st(arr);
	
	
	array_push(arr, 10);
	array_push(arr, 20);
	array_push(arr, 30);

	array_ins(arr, 1, 40);
	
	printf("%i\n", array_at(arr, 1));
	
	array_rem(arr, 1);

	printf("%i\n", array_at(arr, 1));

	printf("%i\n", array_back(arr));
	printf("%i\n", array_pop(arr));
	printf("%i\n", array_back(arr));
	
	puts("Dynamic structure");

	def_darray(int);
	darray(int) da;
	init_dst(da, 100);

	for (size_t i = 0; i < 50; i++)
		array_push(da, i);

	printf("%i\n", array_back(da));
	printf("capacity: %zu | size: %zu\n", st_capacity(da), st_size(da));
	array_pop(da);
	printf("%i\n", array_back(da));
	printf("capacity: %zu | size: %zu\n", st_capacity(da), st_size(da));
	
	stl_free(da);
	
	return 0;
}



