
#include <stdio.h>

#include "../include/stl/array.h"
#include "../include/stl/gen.h"

int main(void)
{
	puts("Static structure");
	def_array(int);
	array(int) arr;
	st_init(arr);

	array_append(arr, 10);
	array_append(arr, 20);
	array_append(arr, 30);

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
	dst_init(da, 100);

	for (size_t i = 0; i < 50; i++)
		array_append(da, i);

	printf("%i\n", array_back(da));
	printf("capacity: %zu | size: %zu\n", st_capacity(da), st_size(da));
	array_pop(da);
	printf("%i\n", array_back(da));
	printf("capacity: %zu | size: %zu\n", st_capacity(da), st_size(da));
	
	st_free(da);
	
	return 0;
}



