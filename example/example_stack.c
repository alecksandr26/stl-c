#include <stdio.h>

#include "../include/stl/stack.h"
#include "../include/stl/gen.h"

mul_def_stack(float, 1, 2, 10, 11, 100);

/* define a dynamic stack */
mul_def_dstack(float, int);
def_dstack(d_ptr(float));

void prints_attributes(stack(float, 100) *stack)
{
	printf("Size: %zu\n", st_size(*stack));
	printf("Capacity: %zu\n", st_capacity(*stack));
}


void print_d_attributes_float(dstack(float) *dstack)
{
	printf("Size: %zu\n", st_size(*dstack));
	printf("Capacity: %zu\n", st_capacity(*dstack));
}

void print_d_attributes_int(dstack(int) *dstack)
{
	printf("Size: %zu\n", st_size(*dstack));
	printf("Capacity: %zu\n", st_capacity(*dstack));
}

void example_float(void)
{
	puts("Static structrue");

	stack(float, 100) stack;
	st_init(stack);
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
	dstack(float) *dstack = st_new(dstack(float));
	
	dst_init(*dstack);
	print_d_attributes_float(dstack);

	puts("Pushing...");

	for (int i = 0; i <= 10; i++)
		stack_push(*dstack, (float) i);
	
	print_d_attributes_float(dstack);

	for (int i = 0; i < 5; i++)
		(void) stack_pop(*dstack);

	puts("Poping...");

	print_d_attributes_float(dstack);
	printf("%f\n", stack_top(*dstack));
	
	st_free(*dstack);
}


void example_dynamic(void)
{
	dstack(int) ds;
	dst_init(ds, 100);

	stack_push(ds, 10);
	stack_push(ds, 20);
	stack_push(ds, 30);

	(void) stack_pop(ds);

	print_d_attributes_int(&ds);

	st_free(ds);
}

int main()
{
	def_stack(d_ptr(float));

	stack(d_ptr(float)) stack;
	st_init(stack);

	printf("%p\n", (void *) stack.con.container);

	
	float var1 = 2.0, var2 = 3.0;
	
	stack_push(stack, &var1);
	
	stack_push(stack, &var2);

	printf("%f\n", *stack_top(stack));

	example_float();
	
	def_stack(d_ptr(float), 100);
	stack(d_ptr(float), 100) *stack_ptr = st_new(stack(d_ptr(float), 100));
	st_init(*stack_ptr);

	stack_push(*stack_ptr, &var1);
	stack_push(*stack_ptr, &var2);
		
	printf("Size: %zu\n", st_size(*stack_ptr));
	printf("Capacity: %zu\n", st_capacity(*stack_ptr));
	printf("%f\n", *stack_top(*stack_ptr));
	

	st_free(*stack_ptr);

	example_dynamic();

	
	return 0;
}

