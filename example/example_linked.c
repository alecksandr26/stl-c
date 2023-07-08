#include <stdio.h>
#include "../include/stl/linked.h"
#include "../include/stl/gen.h"

int main(void)
{
	def_linked(int);
	linked(int) l;
	st_init(l);

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
		
	
	return 0;
}
