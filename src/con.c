
#include <malloc.h>
#include "../include/stl/con.h"

size_t stl_init_con_capacity(void *container, size_t static_container_size, size_t dtype_size)
{
	return (__STL_IS_DYNAMIC_CONTAINER(container))	\
		? malloc_usable_size(container) / dtype_size	\
		: static_container_size / dtype_size;
}




