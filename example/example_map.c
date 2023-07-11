
#include <stdio.h>
#include "../include/stl/map.h"
#include "../include/stl/gen.h"

int main(void)
{
	def_dmap(int, int);
	dmap(int, int) m;
	init_dst(m, 100);
	
	printf("%zu\n", m.con.dtype_size);
	init_st(m.con.container[0]);
	printf("%zu\n", m.con.container[0].con.dtype_size);


	stl_free(m);
	
	
	return 0;
	
}

