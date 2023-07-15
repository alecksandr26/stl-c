#include <unittest.h>
#include <tc.h>

#include "../include/stl/stack.h"
#include "../include/stl/gen.h"
#include "../include/stl/except.h"
#include "../include/stl/def.h"

TESTCASE(StackStaticAllocation) {
	def_stack(float, 11);
	def_stack(float);
	
	TEST(TestDefaultCapacity) {
		stack(float) stack;
		
		init_st(stack); /* Initialize this new stack */
		
		ASSERT(st_capacity(stack) == STL_DEFAULT_STACK_CAPACITY,
		       "st_capacity(stack) Should return the default capacity");
	}

	TEST(TestDefinedCapacity) {
		stack(float, 11) stack;

		init_st(stack); /* Initialize this new stack */
		
		ASSERT(st_capacity(stack) == 11, "The capacity should be equal 11");
	}
} ENDTESTCASE


TESTCASE(StackAdd) {
	/* boilerplate code */
	def_stack(int);
	stack(int) stack;
	init_st(stack);
	int top = 0;

	TEST(TrivialAddition) {
		stack_push(stack, 10);
		
		ASSERT(stack_top(stack) == 10, "Should be 10");
	}

	TEST(EmptyException) {
		top = -1;
		
		try {
			top = stack_top(stack); /* Should throw an exception */
			
			ASSERT(0, "This should never be executed");
		} catch(EmptyStructure) {
			top = st_size(stack);
		} endtry;
		
		ASSERT(top == 0, "It should be 0 because the st_size returns 0");
	}

	TEST(ExhaustingAddition) {
		/* Exhausting addition */
		try {
			for (int i = 1; i <= STL_DEFAULT_STACK_CAPACITY; i++)
				stack_push(stack, i);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} endtry;
	}
} ENDTESTCASE


TESTCASE(StackPoping) {
	/* boilerplate code */
	def_stack(int);
	stack(int) stack;
	init_st(stack);

	TEST(TrivialRemove) {
		stack_push(stack, 10);
		(void) stack_pop(stack);

		ASSERT(st_size(stack) == 0, "Should be zero");
	}


	TEST(RemoveException) {
		stack_push(stack, 10);
		(void) stack_pop(stack);

		try {
			(void) stack_pop(stack); /* This should raise an exception */
			ASSERT(0, "This exception should never be executed");
		} catch(EmptyStructure) {
			ASSERT(st_size(stack) == 0, "Should be zero");
		} endtry;
	}


	TEST(ExhaustingRemoving) {
		/* Exhausting addition */
		try {
			for (int i = 1; i <= STL_DEFAULT_STACK_CAPACITY; i++)
				stack_push(stack, i);
			for (int i = 1; i <= STL_DEFAULT_STACK_CAPACITY; i++)
				(void) stack_pop(stack);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} catch(EmptyStructure) {
			ASSERT(0, "This exception should never be executed");
		} endtry;

		ASSERT(st_size(stack) == 0, "Should be empty the stack");
	}
} ENDTESTCASE

TESTCASE(StackDynamic) {
	def_dstack(float);
	dstack(float) stack;
	init_dst(stack, 10);
	
	TEST(StackInitDynamic) {
		try {
			dstack(float) stack2;
			init_dst(stack2);
			stl_free(stack2);
		} catch(NotEnoughMemory) {
			ASSERT(0, "This exception shoulnd't be happening");
		} endtry;
	}


	TEST(StackDynamicCapacity) {
		ASSERT(st_capacity(stack) >= 10, "Should have the same capacity");
	}

	TEST(InitializeStack) {
		ASSERT(st_size(stack) == 0, "we Hand't introduce any value");
	}
	
	stl_free(stack);
} ENDTESTCASE


TESTCASE(StackDynamicAdditionRemoving) {
	def_dstack(float);
	dstack(float) stack;
	init_dst(stack, 100);

	TEST(TrivialAddition) {
		stack_push(stack, 10.0);
		ASSERT(stack_top(stack) == 10.0, "Should be 10");
	}

	TEST(TrivialDeletion) {
		stack_push(stack, 10.0);
		(void) stack_pop(stack);
		
		ASSERT(st_size(stack) == 0, "Shold be empty");
	}

	TEST(DeletionException) {
		try {
			(void) stack_pop(stack);
			
			ASSERT(0, "This assertin should be never exectued");
		} catch(EmptyStructure) {
			ASSERT(st_size(stack) == 0, "Shold be empty");
		} endtry;
	}
	
	TEST(IncreasingWithAddition) {
		try {
			for (int i = 1; i <= 100; i++)
				stack_push(stack, (float) i);
			for (int i = 1; i <= 100; i++)
				(void) stack_pop(stack);
		} catch(NotEnoughMemory) {
			ASSERT(0, "This exception should never be executed");
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} endtry;
	}

	stl_free(stack);
} ENDTESTCASE


TESTCASE(TestingStackPtr) {
	def_stack(ptr(float));
	stack(ptr(float)) stack;
	init_st(stack);
	float var = 2.0;
	
	TEST(TrivialAddition) {
		stack_push(stack, &var);
		ASSERT(*stack_top(stack) == 2.0, "The Top Should be 2.0");
	}

	TEST(TrivialDeletion) {
		stack_push(stack, &var);
		ASSERT(*stack_pop(stack) == 2.0, "The Poped Should be 2.0");
		ASSERT(st_size(stack) == 0, "Should be empty");
		ASSERT(st_empty(stack) == 1, "Should be empty");
	}
} ENDTESTCASE

NEW_SUIT(SuitTestStack, StackStaticAllocation, StackAdd, StackPoping,
	 StackDynamic,
	 StackDynamicAdditionRemoving,
	 TestingStackPtr);

