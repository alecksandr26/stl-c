#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include <tc.h>
#include <assert.h>

#include "../include/stl/con.h"
#include "../include/stl/ex.h"

unsigned long stl_heapaddr = 0;

unsigned char *stl_alloc_struct(size_t st_size)
{
	unsigned char *st_ptr;
	
	if ((st_ptr = malloc(st_size)) == NULL)
		throw(NotEnoughMemory);

	if (stl_heapaddr < (unsigned long) st_ptr)
		stl_heapaddr = ((unsigned long) st_ptr) + st_size;

	return st_ptr;
}

unsigned char *stl_alloc_container(size_t container_capacity)
{
	unsigned char *container;

	if ((container = malloc(container_capacity)) == NULL)
		throw(NotEnoughMemory);

	if (stl_heapaddr < (unsigned long) container)
		stl_heapaddr = ((unsigned long) container) + container_capacity;

	return container;
}

unsigned char *stl_realloc_container(unsigned char *container_ptr, size_t new_container_capacity)
{
	assert(container_ptr != NULL);

	if ((container_ptr = realloc(container_ptr, new_container_capacity)) == NULL)
		throw(NotEnoughMemoryToRealloc);

	if (stl_heapaddr < (unsigned long) container_ptr)
		stl_heapaddr = ((unsigned long) container_ptr) + new_container_capacity;

	return container_ptr;
}

void stl_free_container(unsigned char *container_ptr, size_t container_capacity)
{
	assert(container_ptr != NULL);
	
	if (stl_heapaddr == ((unsigned long) container_ptr) + container_capacity)
		stl_heapaddr = ((unsigned long) container_ptr);

	free(container_ptr);
}

void stl_free_struct(unsigned char *st_ptr)
{
	assert(st_ptr != NULL);
	
	free(st_ptr);
}



