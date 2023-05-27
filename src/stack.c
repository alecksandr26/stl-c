#include <assert.h>
#include <except.h>

#include "../include/stl/mem.h"
#include "../include/stl/con.h"
#include "../include/stl/stack.h"

Except NotEnoughCapacity = {"NotEnoughCapacity: Not enough capacity at the structure"};
Except EmptyStructure = {"EmptyStructure: The structure doesn't have any element"};

size_t stl_stack_inc(__stl_stack_t *stack)
{
	assert(stack != NULL && "Can't be null");

	if (stack->head + 1 > stack->con.capacity)
		throw_except(NotEnoughCapacity);

	return stack->head++;
}

size_t stl_stack_dec(__stl_stack_t *stack)
{
	assert(stack != NULL && "Can't be null");
	
	if (stack->head == 0)
		throw_except(EmptyStructure);

	return --stack->head;
}

size_t stl_stack_top(__stl_stack_t *stack)
{
	assert(stack != NULL && "Can't be null");
	
	if (stack->head == 0)
		throw_except(EmptyStructure);

	return stack->head - 1;
}


unsigned char *stl_dstack_inc(__stl_stack_t *stack)
{
	if (stack->head + 1 > stack->con.capacity) {
		stl_realloc_container((unsigned char *) stack, sizeof(*stack), stack->con.capacity \
				      * STL_DEFAULT_DSTACK_INCREASE_RATE * stack->con.dtype_size);
		STL_INIT_D_CONTAINER_CAPACITY(stack->con);
	}

	return stack->con.container + (stack->head++ * stack->con.dtype_size);
}


unsigned char *stl_dstack_dec(__stl_stack_t *stack)
{
	if (stack->head <= stack->con.capacity / STL_DEFAULT_DSTACK_INCREASE_RATE) {
		stl_realloc_container((unsigned char *) stack,
				      sizeof(*stack),
				      (stack->head + 1) * stack->con.dtype_size);
		STL_INIT_D_CONTAINER_CAPACITY(stack->con);
	}
	return stack->con.container + (--stack->head * stack->con.dtype_size);
}

