#include <unittest.h>

#undef TEST_DIR 
#define TEST_DIR "test/" 

#undef TEST_OUT
#define TEST_OUT "test.out"

#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1


int main(void)
{
	INCLUDE_SUIT("test_queue.c", SuitTestQueue);
	INCLUDE_SUIT("test_stack.c", SuitTestStack);
	INCLUDE_SUIT("test_con.c", SuitTestCon);
	INCLUDE_SUIT("test_new_st.c", SuitNewFunc);
	INCLUDE_SUIT("test_array.c", SuitTestArray);
	INCLUDE_SUIT("test_linked.c", SuitTestLinked);
	
	ATTACH_EXTRA_FLAGS("lib/libstl.a");
	
	ACTIVE_VALGRIND();

	RUN();
	
	return 0;
}
