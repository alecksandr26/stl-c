
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stl/array.h"
#include "../include/stl/gen.h"
#include "../include/stl/ex.h"

unsigned char *__stl_array_insert_byindex(__stl_array_t *array, size_t ind)
{
	assert(array != NULL);

	if (st_size(*array) < ind)
		throw(InvalidIndex);

	if (st_capacity(*array) ==  st_size(*array)) {
		if (array->con.type == STL_STATIC)
			throw(NotEnoughCapacity);
		array->con.addr = array->con.container =
			stl_realloc_container(array->con.addr,
					      st_capacity(*array)
					      * STL_DEFAULT_DARRAY_INCREASE_RATE
					      * array->con.dtype_size);
		st_capacity(*array) = st_capacity(*array) * STL_DEFAULT_DARRAY_INCREASE_RATE;
	}

	/* Open space throw the array */
	for (size_t i = st_size(*array); i > ind; i--)
		memcpy(array->con.addr + (i * array->con.dtype_size),
		       array->con.addr + ((i - 1) * array->con.dtype_size),
		       array->con.dtype_size);
	
	st_size(*array)++;
	return array->con.addr + (ind * array->con.dtype_size);
}

unsigned char *__stl_array_pop(__stl_array_t *array)
{
	assert(array != NULL);
	
	if (st_size(*array) == 0)
		throw(EmptyStructure);

	if (array->con.type == STL_DYNAMIC
	    && st_size(*array) <= st_capacity(*array) / STL_DEFAULT_DARRAY_INCREASE_RATE) {
		array->con.addr = array->con.container =
			stl_realloc_container(array->con.addr,
					      ((st_capacity(*array)
						/  STL_DEFAULT_DARRAY_INCREASE_RATE) + 1)
					      * array->con.dtype_size);
		st_capacity(*array) = st_capacity(*array) / STL_DEFAULT_DARRAY_INCREASE_RATE + 1;
	}

	return array->con.addr + (st_size(*array)-- - 1) * array->con.dtype_size;
}

void __stl_array_rem(__stl_array_t *array, size_t ind)
{
	assert(array != NULL);
	
	if (st_size(*array) == 0)
		throw(EmptyStructure);

	if (st_size(*array) < ind)
		throw(InvalidIndex);

	if (st_size(*array) <= st_capacity(*array) / STL_DEFAULT_DARRAY_INCREASE_RATE
	    && array->con.type == STL_DYNAMIC) {
		array->con.addr = array->con.container =
			stl_realloc_container(array->con.addr,
					      ((st_capacity(*array)
						/  STL_DEFAULT_DARRAY_INCREASE_RATE) + 1)
					      * array->con.dtype_size);
		st_capacity(*array) = st_capacity(*array) / STL_DEFAULT_DARRAY_INCREASE_RATE + 1;
	}
	
	for (size_t i = ind; i < st_size(*array) - 1; i++)
		memcpy(array->con.addr + (i * array->con.dtype_size),
		       array->con.addr + ((i + 1) * array->con.dtype_size),
		       array->con.dtype_size);

	st_size(*array)--;
}

size_t __stl_array_at(__stl_array_t *array, size_t index)
{
	assert(array != NULL);

	if (st_empty(*array))
		throw(EmptyStructure);
	
	if (st_size(*array) <= index)
		throw(InvalidIndex);

	return index;
}
