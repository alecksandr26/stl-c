#include <assert.h>
#include <tc.h>

#include "../include/stl/mem.h"
#include "../include/stl/con.h"
#include "../include/stl/stack.h"
#include "../include/stl/gen.h"
#include "../include/stl/except.h"

unsigned char *__stl_stack_inc(__stl_stack_t *stack)
{
	assert(stack != NULL && "Can't be null");
	
	if (stack->con.size + 1 > st_capacity(*stack)) {
		if (stack->con.type == STL_STATIC)
			throw(NotEnoughCapacity);
		stack->con.container =
			stl_realloc_container(stack->con.addr, stack->con.capacity
					      * STL_DEFAULT_DSTACK_INCREASE_RATE
					      * stack->con.dtype_size);
		stack->con.capacity *= STL_DEFAULT_DSTACK_INCREASE_RATE;
		stack->con.addr = stack->con.container;
	}
	
	return stack->con.addr + st_size(*stack)++ * stack->con.dtype_size;
}



unsigned char *__stl_stack_dec(__stl_stack_t *stack)
{
	assert(stack != NULL && "Can't be null");
	
	if (stack->con.size == 0)
		throw(EmptyStructure);

	if (stack->con.type == STL_DYNAMIC
	    && stack->con.size <= stack->con.capacity / STL_DEFAULT_DSTACK_INCREASE_RATE) {
		stack->con.addr = stack->con.container =
			stl_realloc_container((unsigned char *) stack->con.container,
					      (stack->con.capacity / STL_DEFAULT_DSTACK_INCREASE_RATE + 1)
					      * stack->con.dtype_size);
		stack->con.capacity = stack->con.capacity / STL_DEFAULT_DSTACK_INCREASE_RATE + 1;
	}

	return stack->con.addr + --stack->con.size * stack->con.dtype_size;
}

size_t __stl_stack_top(__stl_stack_t *stack)
{
	assert(stack != NULL && "Can't be null");
	
	if (stack->con.size == 0)
		throw(EmptyStructure);

	return stack->con.size - 1;
}
