
#include <unittest.h>
#include <stdlib.h>
#include <time.h>

#include "../include/stl/linked.h"
#include "../include/stl/gen.h"
#include "../include/stl/except.h"

TESTCASE(LinkedStaticAllocation) {
	def_linked(int, 11);
	def_linked(int);
	
	TEST(TestDefaultCapacity) {
		linked(int) l;
		init_st(l);

		ASSERT(st_capacity(l) == STL_DEFAULT_LINKED_CAPACITY,
		       "st_capacity(l) Should return the default capacity");
	}

	TEST(TestDefinedCapacity) {
		linked(int, 11) l;
		
		init_st(l); /* Initialize this new l */
		
		ASSERT(st_capacity(l) == 11, "The capacity should be equal 11");
	}
} ENDTESTCASE

TESTCASE(LinkedAdd) {
	def_linked(int);
	linked(int) l;
	init_st(l);
	int back = 0;
	
	TEST(TrivialAddition) {
		linked_push_back(l, 10);
		
		ASSERT(linked_back(l) == 10, "Should be 10");
		ASSERT(linked_front(l) == 10, "Should be 10");
		
		linked_push_front(l, 20);
		
		ASSERT(linked_front(l) == 20, "Should be 10");
	}

	TEST(EmptyException) {
		back = -1;
		
		try {
			back = linked_back(l); /* Should throw an exception */
			
			ASSERT(0, "This should never be executed");
		} catch(EmptyStructure) {
			back = st_size(l);
		} endtry;
		
		ASSERT(back == 0, "It should be 0 because the st_size returns 0");

		back = -1;
		
		try {
			back = linked_front(l); /* Should throw an exception */
			
			ASSERT(0, "This should never be executed");
		} catch(EmptyStructure) {
			back = st_size(l);
		} endtry;
		
		ASSERT(back == 0, "It should be 0 because the st_size returns 0");
	}

	TEST(ExhaustingAdditionBack) {
		/* Exhausting addition */
		try {
			for (int i = 1; i <= STL_DEFAULT_LINKED_CAPACITY; i++)
				linked_push_back(l, i);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} endtry;
		
		ASSERT(linked_back(l) == STL_DEFAULT_LINKED_CAPACITY, "Should be 10");
		ASSERT(linked_front(l) == 1, "Should be 10");
	}

	TEST(ExhaustingAdditionFront) {
		try {
			for (int i = 1; i <= STL_DEFAULT_LINKED_CAPACITY; i++)
				linked_push_front(l, i);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} endtry;
		
		ASSERT(linked_back(l) == 1, "Should be 10");
		ASSERT(linked_front(l) == STL_DEFAULT_LINKED_CAPACITY, "Should be 10");
	}
	
} ENDTESTCASE

TESTCASE(LinkedInsertion) {
	def_linked(int);
	linked(int) l;
	init_st(l);

	linked_push_back(l, 1);
	linked_push_back(l, 3);
	linked_push_back(l, 4);
	
	TEST(TrivialInsertion) {
		linked_ins(l, 1, 2);
		ASSERT(linked_at(l, 1) == 2, "linked_at(l, 1) == 2");
	}

	TEST(InvalidIndexException) {
		int back = 1;
		try {
			linked_ins(l, st_size(l) + 1, 2);
			ASSERT(0, "This should never be executed");
		} catch(InvalidIndex) {
			back = 0;
		} endtry;
		
		ASSERT(back == 0, "It should be 0 because the st_size returns 0");
	}
	
	TEST(ExhaustingInsertion) {
		srand(time(0));
		
		for (int i = 1; i <= STL_DEFAULT_LINKED_CAPACITY - 3; i++) {
			int irand = rand() % st_size(l);
			try {
				linked_ins(l, irand, i);
			} catch(InvalidIndex) {
				ASSERT(0, "Should be able to do handle exhausting");
			} endtry;
			
			ASSERT(linked_at(l, irand) == i, "Shold hold the number");
		}
	}
} ENDTESTCASE

TESTCASE(LinkedPop) {
	def_linked(int);
	linked(int) l;
	init_st(l);

	linked_push_back(l, 1);
	linked_push_back(l, 3);
	linked_push_back(l, 4);
	
	TEST(TrivialPop) {
		(void) linked_pop_back(l);
		
		ASSERT(linked_front(l) == 1, "Should be 10");
		ASSERT(linked_back(l) == 3, "Should be 10");
		
		(void) linked_pop_front(l);
		
		ASSERT(linked_front(l) == 3, "Should be 10");
		ASSERT(linked_back(l) == 3, "Should be 10");
	}

	TEST(EmptyExceptionFront) {
		int back = -1;

		(void) linked_pop_back(l);
		(void) linked_pop_back(l);
		(void) linked_pop_back(l);
		
		try {
			back = linked_back(l); /* Should throw an exception */
			
			ASSERT(0, "This should never be executed");
		} catch(EmptyStructure) {
			back = st_size(l);
		} endtry;
		
		ASSERT(back == 0, "It should be 0 because the st_size returns 0");
	}

	TEST(EmptyExceptionBack) {
		int back = -1;

		(void) linked_pop_front(l);
		(void) linked_pop_front(l);
		(void) linked_pop_front(l);
		
		try {
			back = linked_front(l); /* Should throw an exception */
			
			ASSERT(0, "This should never be executed");
		} catch(EmptyStructure) {
			back = st_size(l);
		} endtry;
		
		ASSERT(back == 0, "It should be 0 because the st_size returns 0");
	}

	TEST(ExhaustingPoping) {
		/* Exhausting Poping */
		try {
			for (int i = 1; i <= STL_DEFAULT_LINKED_CAPACITY - 3; i++)
				linked_push_back(l, i);

			for (int i = 1; i <= STL_DEFAULT_LINKED_CAPACITY; i++)
				(void) linked_pop_back(l);
			
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} catch(InvalidIndex) {
			ASSERT(0, "This exception should never be executed");
		} catch(EmptyStructure) {
			ASSERT(0, "This exception should never be executed");
		} endtry;
		
		ASSERT(st_size(l) == 0, "Should be 0");


		try {
			for (int i = 1; i <= STL_DEFAULT_LINKED_CAPACITY; i++)
				linked_push_back(l, i);

			for (int i = 1; i <= STL_DEFAULT_LINKED_CAPACITY; i++)
				(void) linked_pop_front(l);
			
		} catch(NotEnoughCapacity) {
			ASSERT(0, "This exception should never be executed");
		} catch(InvalidIndex) {
			ASSERT(0, "This exception should never be executed");
		} catch(EmptyStructure) {
			ASSERT(0, "This exception should never be executed");
		} endtry;
		
		ASSERT(st_size(l) == 0, "Should be 0");
	}
} ENDTESTCASE


TESTCASE(LinkedDeletion) {
	def_linked(int);
	linked(int) l;
	init_st(l);

	TEST(TrivialDeletion) {
		linked_push_back(l, 1);
		linked_push_back(l, 3);
		linked_push_back(l, 4);
		
		(void) linked_rem(l, 0);
		ASSERT(linked_at(l, 0) == 3, "linked_at(l, 0) == 3");
	}

	TEST(InvalidIndexException) {
		int back = 1;
		
		linked_push_back(l, 1);
		linked_push_back(l, 3);
		linked_push_back(l, 4);
		
		try {
			(void) linked_rem(l, st_size(l));
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
		
		for (int i = 1; i <= STL_DEFAULT_LINKED_CAPACITY; i++)
			linked_push_back(l, i);

		for (int i = 1; i <= STL_DEFAULT_LINKED_CAPACITY; i++) {
			size_t irand = (size_t) rand() % st_size(l);
			int element = linked_at(l, irand);
			try {
				(void) linked_rem(l, irand);
			} catch(InvalidIndex) {
				ASSERT(0, "Should be able to do handle exhausting");
			} catch(EmptyStructure) {
				ASSERT(0, "Should be able to do handle exhausting");
			} endtry;
			
			if (irand < st_size(l) - 1 && !st_empty(l)) {
				ASSERT(element != linked_at(l, irand), "Should be different");
			}
		}

		ASSERT(st_empty(l), "SHould be empty");
	}
} ENDTESTCASE


TESTCASE(DynamicLinked) {
	def_dlinked(int);
	dlinked(int) dl;
	
	TEST(TestDefaultCapacity) {
		init_dst(dl);	/* Alloc the memory */
		ASSERT(st_capacity(dl) == STL_DEFAULT_LINKED_CAPACITY,
		       "st_capacity(dl) should have the default capacity");
		stl_free(dl);
	}

	TEST(TestDefiniedCapacity) {
		init_dst(dl, 100);	/* Alloc the memory */
		ASSERT(st_capacity(dl) == 100,
		       "st_capacity(dl) should have the default capacity");
		stl_free(dl);
	}
} ENDTESTCASE


TESTCASE(DynamicLinkedIncreaseDecrease) {
	def_dlinked(int);
	dlinked(int) dl;
	init_dst(dl, 2);	/* Alloc the memory */

	TEST(Increase) {
		try {
			for (int i = 1; i <= 100; i++)
				linked_push_back(dl, i);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "Should not be executed");
		} catch(InvalidIndex) {
			ASSERT(0, "Should not be executed");
		} endtry;

		ASSERT(st_size(dl) == 100, "Should be size");
		ASSERT(st_capacity(dl) > 100, "Should have a greater capacity");
	}


	TEST(Dencrease) {
		try {
			for (int i = 1; i <= 100; i++)
				linked_push_back(dl, i);
			
			for (int i = 1; i <= 100; i++)
				(void) linked_pop_back(dl);
		} catch(NotEnoughCapacity) {
			ASSERT(0, "Should not be executed");
		} catch(InvalidIndex) {
			ASSERT(0, "Should not be executed");
		} endtry;

		ASSERT(st_size(dl) == 0, "Should be size");
		ASSERT(st_capacity(dl) == 2, "Should be the initialized capacity");
	}

	stl_free(dl);
} ENDTESTCASE


NEW_SUIT(SuitTestLinked, LinkedStaticAllocation, LinkedAdd,
	 LinkedInsertion, LinkedPop, LinkedDeletion,
	 DynamicLinked, DynamicLinkedIncreaseDecrease);
