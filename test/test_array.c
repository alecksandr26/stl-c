
#include <unittest.h>
#include <stdlib.h>
#include <time.h>

#include "../include/stl/array.h"
#include "../include/stl/gen.h"
#include "../include/stl/except.h"

TESTCASE(ArrayStaticAllocation) {
	def_array(int, 11);
	def_array(int);
	
	TEST(TestDefaultCapacity) {
		array(int) arr;
		init_st(arr);

		ASSERT(st_capacity(arr) == STL_DEFAULT_ARRAY_CAPACITY,
		       "st_capacity(arr) Should return the default capacity");
	}

	TEST(TestDefinedCapacity) {
		array(int, 11) arr;
		
		init_st(arr); /* Initialize this new arr */
		
		ASSERT(st_capacity(arr) == 11, "The capacity should be equal 11");
	}
} ENDTESTCASE

TESTCASE(ArrayAdd) {
	def_array(int);
	array(int) arr;
	init_st(arr);
	int back = 0;
	
	TEST(TrivialAddition) {
		array_push(arr, 10);
		
		ASSERT(array_back(arr) == 10, "Should be 10");
		ASSERT(array_front(arr) == 10, "Should be 10");
	}

	TEST(EmptyException) {
		back = -1;
		
		try {
			back = array_back(arr); /* Should throw an exception */
			
			ASSERT(0, "This should never be executed");
		} catch(EmptyStructure) {
			back = st_size(arr);
		} endtry;
		
		ASSERT(back == 0, "It should be 0 because the st_size returns 0");
	}

	TEST(ExhaustingAddition) {
		/* Exhausting addition */
		try {
			for (int i = 1; i <= STL_DEFAULT_ARRAY_CAPACITY; i++)
				array_push(arr, i);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} endtry;
		
		ASSERT(array_back(arr) == STL_DEFAULT_ARRAY_CAPACITY, "Should be 10");
		ASSERT(array_front(arr) == 1, "Should be 10");
	}
	
} ENDTESTCASE

TESTCASE(ArrayInsertion) {
	def_array(int);
	array(int) arr;
	init_st(arr);

	array_push(arr, 1);
	array_push(arr, 3);
	array_push(arr, 4);

	TEST(TrivialInsertion) {
		array_ins(arr, 1, 2);
		ASSERT(array_at(arr, 1) == 2, "array_at(arr, 1) == 2");
	}

	TEST(InvalidIndexException) {
		int back = 1;
		try {
			array_ins(arr, st_size(arr) + 1, 2);
			ASSERT(0, "This should never be executed");
		} catch(InvalidIndex) {
			back = 0;
		} endtry;
		
		ASSERT(back == 0, "It should be 0 because the st_size returns 0");
	}
	
	TEST(ExhaustingInsertion) {
		srand(time(0));
		
		for (int i = 1; i <= STL_DEFAULT_ARRAY_CAPACITY - 3; i++) {
			int irand = rand() % st_size(arr);
			try {
				array_ins(arr, irand, i);
			} catch(InvalidIndex) {
				ASSERT(0, "Should be able to do handle exhausting");
			} endtry;
			
			ASSERT(array_at(arr, irand) == i, "Shold hold the number");
		}
	}
} ENDTESTCASE

TESTCASE(ArrayPop) {
	def_array(int);
	array(int) arr;
	init_st(arr);

	array_push(arr, 1);
	array_push(arr, 3);
	array_push(arr, 4);
	
	TEST(TrivialPop) {
		(void) array_pop(arr);
		
		ASSERT(array_front(arr) == 1, "Should be 10");
		ASSERT(array_back(arr) == 3, "Should be 10");
	}

	TEST(EmptyException) {
		int back = -1;

		(void) array_pop(arr);
		(void) array_pop(arr);
		(void) array_pop(arr);
		
		try {
			back = array_back(arr); /* Should throw an exception */
			
			ASSERT(0, "This should never be executed");
		} catch(EmptyStructure) {
			back = st_size(arr);
		} endtry;
		
		ASSERT(back == 0, "It should be 0 because the st_size returns 0");
	}

	TEST(ExhaustingPoping) {
		/* Exhausting Poping */
		try {
			for (int i = 1; i <= STL_DEFAULT_ARRAY_CAPACITY - 3; i++)
				array_push(arr, i);

			for (int i = 1; i <= STL_DEFAULT_ARRAY_CAPACITY; i++)
				(void) array_pop(arr);
			
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} catch(InvalidIndex) {
			ASSERT(0, "This exception should never be executed");
		} catch(EmptyStructure) {
			ASSERT(0, "This exception should never be executed");
		} endtry;
		
		ASSERT(st_size(arr) == 0, "Should be 0");
	}
} ENDTESTCASE


TESTCASE(ArrayDeletion) {
	def_array(int);
	array(int) arr;
	init_st(arr);

	array_push(arr, 1);
	array_push(arr, 3);
	array_push(arr, 4);

	TEST(TrivialDeletion) {
		array_rem(arr, 0);
		ASSERT(array_at(arr, 0) == 3, "array_at(arr, 0) == 3");
	}

	TEST(InvalidIndexException) {
		int back = 1;
		try {
			array_rem(arr, st_size(arr) + 1);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} catch(InvalidIndex) {
			back = 0;
		} catch(EmptyStructure) {
			ASSERT(0, "This exception should never be executed");
		} endtry;
		
		ASSERT(back == 0, "It should be 0");
	}
	
	TEST(ExhaustingDeletion) {
		srand(time(0));
		
		for (int i = 1; i <= STL_DEFAULT_ARRAY_CAPACITY - 3; i++)
			array_push(arr, i);

		for (int i = 1; i <= STL_DEFAULT_ARRAY_CAPACITY; i++) {
			int irand = rand() % st_size(arr);
			try {
				array_rem(arr, irand);
			} catch(InvalidIndex) {
				ASSERT(0, "Should be able to do handle exhausting");
			} catch(EmptyStructure) {
				ASSERT(0, "Should be able to do handle exhausting");
			} endtry;

		}

		ASSERT(st_empty(arr), "SHould be empty");
	}
} ENDTESTCASE


TESTCASE(DynamicArray) {
	def_darray(int);
	darray(int) darr;
	
	TEST(TestDefaultCapacity) {
		init_dst(darr);	/* Alloc the memory */
		ASSERT(st_capacity(darr) == STL_DEFAULT_ARRAY_CAPACITY,
		       "st_capacity(darr) should have the default capacity");
		stl_free(darr);
	}

	TEST(TestDefiniedCapacity) {
		init_dst(darr, 100);	/* Alloc the memory */
		ASSERT(st_capacity(darr) == 100,
		       "st_capacity(darr) should have the default capacity");
		stl_free(darr);
	}
} ENDTESTCASE


TESTCASE(DynamicArrayIncreaseDecrease) {
	def_darray(int);
	darray(int) darr;
	init_dst(darr, 2);	/* Alloc the memory */

	TEST(Increase) {
		try {
			for (int i = 1; i <= 100; i++)
				array_push(darr, i);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "Should not be executed");
		} catch(InvalidIndex) {
			ASSERT(0, "Should not be executed");
		} endtry;

		ASSERT(st_size(darr) == 100, "Should be size");
		ASSERT(st_capacity(darr) > 100, "Should have a greater capacity");
	}


	TEST(Dencrease) {
		try {
			for (int i = 1; i <= 100; i++)
				array_push(darr, i);
			
			for (int i = 1; i <= 100; i++)
				(void) array_pop(darr);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "Should not be executed");
		} catch(InvalidIndex) {
			ASSERT(0, "Should not be executed");
		} endtry;

		ASSERT(st_size(darr) == 0, "Should be size");
		ASSERT(st_capacity(darr) == 2, "Should be the initialized capacity");
	}

	stl_free(darr);
} ENDTESTCASE


NEW_SUIT(SuitTestArray, ArrayStaticAllocation, ArrayAdd,
	 ArrayInsertion, ArrayPop, ArrayDeletion,
	 DynamicArray, DynamicArrayIncreaseDecrease);
