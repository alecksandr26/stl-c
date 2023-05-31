#include <unittest.h>
#include "../include/stl/queue.h"
#include "../include/stl/ex.h"

TESTCASE(InitStaticQueue) {
	def_queue(int);
	def_queue(int, 11);
	
	TEST(StaticAllocation) {
		queue(int) queue;
		queue_init(queue);

		ASSERT(STL_DEFAULT_QUEUE_CAPACITY == queue_capacity(queue),
		       "Should have the default capacity");
	}

	TEST(DefinedStaticAllocation) {
		queue(int, 11) queue;
		queue_init(queue);

		ASSERT(queue_capacity(queue) == 11,
		       "Should have the default capacity");
		
	}
} ENDTESTCASE


TESTCASE(QueueAddition) {
	def_queue(int);
	def_queue(int, 10);
	
	TEST(QueueTrivialAddition) {
		queue(int) queue;
		queue_init(queue);

		queue_push(queue, 10);
		ASSERT(queue_size(queue) == 1, "The size of the queue should be increaded");
		ASSERT(queue_front(queue) == 10, "The front should be equal to 10");
		ASSERT(10 == queue_front(queue), "Testing the macro");
		int front = queue_front(queue);
		
		ASSERT(front == 10, "Testing the macro");
	}

	TEST(QueueAddition) {
		queue(int, 10) queue;
		queue_init(queue);
		
		queue_push(queue, 10);
		queue_push(queue, 20);
		queue_push(queue, 40);

		ASSERT(10 == queue_front(queue), "After some insertions it should be 10");
		ASSERT(queue_back(queue) == 40, "SHould be the last element value");
	}

	TEST(ExhaustingAddition) {
		queue(int) queue;
		queue_init(queue);

		try {
			for (int i = 0; i < STL_DEFAULT_QUEUE_CAPACITY; i++)
				queue_push(queue, i);
		} except(NotEnoughCapacity) {
			ASSERT(0, "This assert should never be executed");
		} endtry;

		ASSERT(queue_front(queue) == 0, "Should be equal to 0");
		ASSERT(queue_back(queue) == STL_DEFAULT_QUEUE_CAPACITY - 1,
		       "Should be equal to its max capacity");
	}
} ENDTESTCASE


TESTCASE(QueueDeleting) {
	def_queue(int);
	queue(int) queue;
	queue_init(queue);
	
	TEST(QueueTrivialDeletion) {
		queue_push(queue, 10);

		ASSERT(queue_pop(queue) == 10, "Should be equal to 10");
		ASSERT(queue_size(queue) == 0, "Should be equal to 0");

		queue_push(queue, 10);
		ASSERT(queue_size(queue) == 1, "Should be equal to 1");
		(void) queue_pop(queue);
		ASSERT(queue_size(queue) == 0, "Should be equal to 0");
	}
	
	TEST(ExhaustingDeletion) {
		try {
			for (int i = 0; i < STL_DEFAULT_QUEUE_CAPACITY; i++)
				queue_push(queue, i);

			ASSERT(queue_size(queue) == STL_DEFAULT_QUEUE_CAPACITY,
			       "Should be equal to its max capacity");
			
			for (int i = 0; i < STL_DEFAULT_QUEUE_CAPACITY; i++)
				(void) queue_pop(queue);

			ASSERT(queue_size(queue) == 0,
			       "Now should be equal to zero");
			
		} except(NotEnoughCapacity) {
			ASSERT(0, "This assert should never be executed");
		} except(EmptyStructure) {
			ASSERT(0, "This assert should never be executed");
		} endtry;
	}
} ENDTESTCASE

TESTCASE(DynamicAllocationQueue) {
	def_dqueue(int);
	
	TEST(InitDynamic) {
		dqueue(int) *dqueue = new_dqueue(int, 100);

		ASSERT(dqueue != NULL, "Can't be null");
		dqueue_init(dqueue);

		ASSERT(dqueue_capacity(dqueue) >= 100, "Should be greater or equal to 100");
		
		stl_free(dqueue);
	}

	TEST(InitDynamic) {
		dqueue(int) *dqueue = new_dqueue(int);

		ASSERT(dqueue != NULL, "Can't be null");
		dqueue_init(dqueue);

		ASSERT(dqueue_capacity(dqueue) >= STL_DEFAULT_DQUEUE_CAPACITY);
		
		stl_free(dqueue);
	}
} ENDTESTCASE


TESTCASE(DynamicQueueAddition) {
	def_dqueue(int);
	
	dqueue(int) *dqueue = new_dqueue(int);
	dqueue_init(dqueue);
	
	TEST(QueueTrivialAddition) {
		dqueue_push(dqueue, 10);
		ASSERT(dqueue_size(dqueue) == 1, "The size of the queue should be increaded");
		ASSERT(dqueue_front(dqueue) == 10, "The front should be equal to 10");
		ASSERT(10 == dqueue_front(dqueue), "Testing the macro");
		int front = dqueue_front(dqueue);
		
		ASSERT(front == 10, "Testing the macro");
	}

	TEST(QueueAddition) {
		dqueue(int) *dq = new_dqueue(int, 10);
		dqueue_init(dq);
		
		dqueue_push(dq, 10);
		dqueue_push(dq, 20);
		dqueue_push(dq, 40);

		ASSERT(10 == dqueue_front(dq), "After some insertions it should be 10");
		ASSERT(dqueue_back(dq) == 40, "SHould be the last element value");
		
		stl_free(dq);
	}

	TEST(ExhaustingAddition) {
		try {
			for (int i = 0; i < STL_DEFAULT_QUEUE_CAPACITY; i++)
				dqueue_push(dqueue, i);
		} except(NotEnoughCapacity) {
			ASSERT(0, "This assert should never be executed");
		} endtry;

		ASSERT(dqueue_front(dqueue) == 0, "Should be equal to 0");
		ASSERT(dqueue_back(dqueue) == STL_DEFAULT_QUEUE_CAPACITY - 1,
		       "Should be equal to its max capacity");
	}

	stl_free(dqueue);
} ENDTESTCASE


TESTCASE(DynamicQueueDeleting) {
	def_dqueue(int);
	dqueue(int) *dqueue = new_dqueue(int);
	dqueue_init(dqueue);
	
	TEST(QueueTrivialDeletion) {
		dqueue_push(dqueue, 10);

		ASSERT(dqueue_pop(dqueue) == 10, "Should be equal to 10");
		ASSERT(dqueue_size(dqueue) == 0, "Should be equal to 0");

		dqueue_push(dqueue, 10);
		ASSERT(dqueue_size(dqueue) == 1, "Should be equal to 1");
		(void) dqueue_pop(dqueue);
		ASSERT(dqueue_size(dqueue) == 0, "Should be equal to 0");
	}
	
	TEST(ExhaustingDeletion) {
		try {
			for (int i = 0; i < STL_DEFAULT_QUEUE_CAPACITY; i++)
				dqueue_push(dqueue, i);

			ASSERT(dqueue_size(dqueue) == STL_DEFAULT_QUEUE_CAPACITY,
			       "Should be equal to its max capacity");
			
			for (int i = 0; i < STL_DEFAULT_QUEUE_CAPACITY; i++)
				(void) dqueue_pop(dqueue);

			ASSERT(dqueue_size(dqueue) == 0,
			       "Now should be equal to zero");
			
		} except(NotEnoughCapacity) {
			ASSERT(0, "This assert should never be executed");
		} except(EmptyStructure) {
			ASSERT(0, "This assert should never be executed");
		} endtry;
	}
	
	stl_free(dqueue);
} ENDTESTCASE


TESTCASE(TestingQueuePointerSupport) {
	def_queue(d_ptr(float));
	queue(d_ptr(float)) queue;
	queue_init(queue);
	float var = 2.0;
	
	TEST(TrivialAddition) {
		queue_push(queue, &var);
		ASSERT(*queue_front(queue) == 2.0, "Should be 2.0");
	}

	TEST(TrivialDeletion) {
		queue_push(queue, &var);
		ASSERT(*queue_pop(queue) == 2.0, "Should be 2.0");
		ASSERT(queue_size(queue) == 0, "Should be cero");
		ASSERT(queue_empty(queue) == 1, "Should be empty");
	}
} ENDTESTCASE


NEW_SUIT(SuitTestQueue, InitStaticQueue, QueueAddition, QueueDeleting,
	 DynamicAllocationQueue, DynamicQueueAddition, DynamicQueueDeleting,
	 TestingQueuePointerSupport);
