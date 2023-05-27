#include <unittest.h>

#undef TEST_DIR 
#define TEST_DIR "test/" 

#undef TEST_OUT
#define TEST_OUT "test.out"


#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1


int main()
{
	INCLUDE_SUIT("test_stack.c", SuitTestStack);

	ATTACH_EXTRA_FLAGS("lib/libstl.a");
	
	ACTIVE_VALGRIND();

	RUN();
	
	return 0;
}
