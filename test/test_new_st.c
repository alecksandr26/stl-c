
#include <unittest.h>
#include <malloc.h>
#include <string.h>

#include "../include/stl/stack.h"
#include "../include/stl/queue.h"
#include "../include/stl/gen.h"

TESTCASE(TestNewAllocation) {
	def_stack(int);
	def_dstack(int);
	
	TEST(StaticAllocation) {
		stack(int) *s = new_st(stack(int));
		init_st(*s);

		ASSERT(st_capacity(*s) == STL_DEFAULT_STACK_CAPACITY);
		stl_free(*s);
	}
	
	TEST(DynamicAllocation) {
		dstack(int) *ds = new_st(dstack(int));
		init_dst(*ds, 100);
		
		ASSERT(st_capacity(*ds) == 100);
		
		stl_free(*ds);
	}	
} ENDTESTCASE

NEW_SUIT(SuitNewFunc, TestNewAllocation);
