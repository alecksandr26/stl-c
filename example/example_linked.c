#include <stdio.h>
#include <assert.h>
#include "../include/stl/linked.h"
#include "../include/stl/gen.h"

void example_static(void)
{
	def_linked(int);
	linked(int) l;
	init_st(l);

	linked_push_back(l, 10);
	linked_push_back(l, 20);
	linked_push_back(l, 30);
	linked_push_back(l, 40);
	linked_push_back(l, 50);
	
	printf("%i\n", linked_front(l));
	printf("%i\n", linked_back(l));
	puts("");
	
	linked_push_front(l, 0);
	linked_push_front(l, -10);

	printf("%i\n", linked_front(l));
	printf("%i\n", linked_back(l));
	puts("");

	(void) linked_pop_front(l);
	printf("%i\n", linked_front(l));
	
	(void) linked_pop_front(l);
	printf("%i\n", linked_front(l));

	puts("");

	linked_push_front(l, -1);
	linked_push_front(l, 0);

	printf("%i\n", linked_front(l));

	puts("");
	(void) linked_pop_back(l);
	printf("%i\n", linked_back(l));
	

	printf("at 5: %i\n", linked_at(l, 5));
	linked_ins(l, 5, 200);
	printf("at 5: %i\n", linked_at(l, 5));
	printf("at 6: %i\n", linked_at(l, 6));

	(void) linked_rem(l, 5);
	printf("at 5: %i\n", linked_at(l, 5));
}

void example_dynamic(void)
{
	def_dlinked(int);
	dlinked(int) l;
	init_dst(l, 100);

	linked_push_back(l, 10);
	linked_push_back(l, 20);
	linked_push_back(l, 30);
	linked_push_back(l, 40);
	linked_push_back(l, 50);

	printf("%i\n", linked_front(l));
	printf("%i\n", linked_back(l));
	printf("capacity: %zu\n", st_capacity(l));
	printf("size: %zu\n", st_size(l));
	puts("");

	printf("%i\n", linked_at(l, 2));
	(void) linked_rem(l, 2);
	printf("%i\n", linked_at(l, 2));
	
	printf("capacity: %zu\n", st_capacity(l));
	printf("size: %zu\n", st_size(l));
	puts("");

	printf("%i\n", linked_at(l, 2));
	(void) linked_rem(l, 2);
	printf("%i\n", linked_at(l, 2));
	printf("capacity: %zu\n", st_capacity(l));
	printf("size: %zu\n", st_size(l));
	puts("");
	
	stl_free(l);
}

int main(void)
{
	example_dynamic();
	
	def_linked(int);
	linked(int) l;
	init_st(l);

	linked_push_back(l, 10);
	linked_push_back(l, 20);
	linked_push_back(l, 30);
	linked_push_back(l, 40);
	linked_push_back(l, 50);

	

	
	return 0;
}
