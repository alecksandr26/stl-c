
#include <assert.h>
#include <stdlib.h>
#include "../include/stl/array.h"
#include "../include/stl/ex.h"
#include "../include/stl/con.h"

size_t __stl_array_insert_byindex(__stl_array_t *array, size_t ind)
{
	int i;
	
	assert(array != NULL);

	if (array_size(*array) < ind && !array_empty(*array))
		throw(InvalidIndex);

	/* Open space throw the array */
	for (i = array_size(*array); i > (int) ind; i--)
		;
}



