
#include <stdio.h>
#include "../include/stl/map.h"
#include "../include/stl/gen.h"

int main(void)
{
	def_map(int, int);
	map(int, int) m;
	init_st(m);

	map_ins(m, 10, 4);
	map_ins(m, 10, 5);
	
	
	return 0;
	
}

