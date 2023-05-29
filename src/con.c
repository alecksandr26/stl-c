
#include <malloc.h>
#include "../include/stl/con.h"

size_t stl_init_con_capacity(unsigned char *container, size_t static_container_size, size_t dtype_size)
{
	printf("%zu\n", malloc_usable_size(container));
	
	return (__STL_IS_DYNAMIC_CONTAINER(container))	\
		? malloc_usable_size(container) / dtype_size	\
		: static_container_size / dtype_size;
}




