#include <stdio.h>

#include "../include/stl/stack.h"

mul_def_stack(float, 1, 2, 10, 11, 100);

/* define a dynamic stack */
mul_def_dstack(float, int);

void prints_attributes(stack(float, 100) *stack)
{
	printf("Size: %zu\n", stack_size(*stack));
	printf("Capacity: %zu\n", stack_capacity(*stack));
}


void print_d_attributes(dstack(float) *dstack)
{
	printf("Size: %zu\n", dstack_size(dstack));
	printf("Capacity: %zu\n", dstack_capacity(dstack));
}

void example_float(void)
{
	puts("Static structrue");

	stack(float, 100) stack;
	stack_init(stack);
	prints_attributes(&stack);
	
	puts("Pushig...");

	for (int i = 0; i <= 10; i++)
		stack_push(stack, (float) i);

	prints_attributes(&stack);
	
	puts("Poping...");

	for (int i = 0; i < 5; i++)
		(void) stack_pop(stack);
	
	prints_attributes(&stack);
	
	/* Dynamic structure */
	puts("\nDynamic structrue");
	dstack(float) *dstack = new_dstack(float);
	dstack_init(dstack);
	print_d_attributes(dstack);

	puts("Pushing...");

	for (int i = 0; i <= 10; i++)
		dstack_push(dstack, (float) i);
	
	print_d_attributes(dstack);

	for (int i = 0; i < 5; i++)
		(void) dstack_pop(dstack);

	puts("Poping...");

	print_d_attributes(dstack);
	printf("%f\n", dstack_top(dstack));

	stl_free(dstack);
}

int main()
{
	def_stack(d_ptr(float));
	stack(d_ptr(float)) stack;
	stack_init(stack);
	
	float var1 = 2.0, var2 = 3.0;
	
	stack_push(stack, &var1);
	stack_push(stack, &var2);

	printf("%f\n", *stack_top(stack));
	
	
	
	return 0;
}

