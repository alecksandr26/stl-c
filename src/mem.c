#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include <except.h>

#include "../include/stl/ex.h"

unsigned long stl_heapaddr = 0;

unsigned char *stl_alloc_struct(size_t st_size, size_t container_size)
{
	unsigned char *st_ptr, *container_ptr;
	
	if ((st_ptr = malloc(st_size)) == NULL)
		throw_except(NotEnoughMemory);

	if ((container_ptr = malloc(container_size)) == NULL)
		throw_except(NotEnoughMemory);

	if (stl_heapaddr < (unsigned long) container_ptr)
		stl_heapaddr = ((unsigned long) container_ptr) + malloc_usable_size(container_ptr);
	
	memcpy(st_ptr + st_size - sizeof(void *), &container_ptr, sizeof(void *));
	return st_ptr;
}

void stl_realloc_container(unsigned char *st_ptr, size_t st_size, size_t new_container_size)
{
	unsigned char *container_ptr;

	memcpy(&container_ptr, st_ptr + st_size - sizeof(void *), sizeof(void *));

	if ((container_ptr = realloc(container_ptr, new_container_size)) == NULL)
		throw_except(NotEnoughMemoryToRealloc);

	if (stl_heapaddr < (unsigned long) container_ptr)
		stl_heapaddr = ((unsigned long) container_ptr) + new_container_size;

	memcpy(st_ptr + st_size - sizeof(void *), &container_ptr, sizeof(void *));
}


void stl_free_struct(unsigned char *st_ptr, size_t st_size, size_t container_size)
{
	unsigned char *container_ptr;

	memcpy(&container_ptr, st_ptr + st_size - sizeof(void *), sizeof(void *));
	
	if (stl_heapaddr == ((unsigned long) container_ptr) + container_size)
		stl_heapaddr = ((unsigned long) container_ptr);

	free(container_ptr);
	free(st_ptr);
}



