
#include <stdio.h>
#include "../include/stl/map.h"
#include "../include/stl/gen.h"

int main(void)
{
	def_map(int, int);
	map(int, int) m;
	init_st(m);

	map_ins(m, 10, 4);
	map_ins(m, 20, 5);
	
	printf("%i\n", map_get(m, 20));
	printf("%i\n", map_get(m, 10));

	int key2 = 20;
	printf("%i\n", map_get(m, key2));

	map_rep(m, 20, 6);
	printf("%i\n", map_get(m, key2));

	printf("%i\n", map_rem(m, key2));

	printf("%i\n", map_get(m, key2));
	
	return 0;
	
}

