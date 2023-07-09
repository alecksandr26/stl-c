#include <unittest.h>
#include <malloc.h>
#include <string.h>

#include "../include/stl/con.h"

typedef struct {
		char foo;
	} foo;

TESTCASE(InitStaticContainer) {
	typedef struct  {
		int age;
		char name[100];
	} person;

	typedef struct {
		size_t head;
	} stack;
	
	TEST(InitStatic) {
		STL_CONTAINER(0, float, 10) container; /* Create the container */
		STL_INIT_CONTAINER(container, float, foo, sizeof(container.container));
		
		ASSERT(sizeof(container.container) >= 10 * sizeof(float),
		       "It shold create the frame of that size");
	}

	TEST(InitStaticStruct) {
		STL_CONTAINER(0, person, 10) container; /* Create the container */
		STL_INIT_CONTAINER(container, person, foo, sizeof(container.container));
		
		ASSERT(sizeof(container.container) >= 10 * sizeof(person));
		ASSERT(container.capacity >= 10, "The capacity should be 10");
	}

	TEST(IsStatic) {
		STL_CONTAINER(0, float, 10) container; /* Create the container */
		ASSERT(STL_IS_DYNAMIC_CONTAINER(container.container) == 0, "It should be false");
	}

	TEST(AssigningSTsize) {
		STL_CONTAINER(0, float, 10) container; /* Create the container */
		STL_INIT_CONTAINER(container, float, stack, sizeof(container.container));
		
		ASSERT(container.st_size == sizeof(stack), "IT should have this structure size");
	}

} ENDTESTCASE


TESTCASE(InitDynamicContainer) {
	typedef struct  {
		int age;
		char name[100];
	} person;

	typedef struct {
		size_t head;
	} stack;

	STL_DCONTAINER(0, float) dcontainer; /* Create the dynamic container */
	STL_INIT_DCONTAINER(dcontainer, float, stack, 10);

	TEST(InitDynamic) {
		ASSERT(dcontainer.capacity >= 10,
		       "It shold create the frame of that size");
	}

	TEST(InitDynamicStruct) {
		STL_DCONTAINER(0, person) dcontainer2; /* Create the dynamic container */

		STL_INIT_DCONTAINER(dcontainer2, person, foo, 10);
		
		ASSERT(dcontainer2.container != NULL, "Shouldn't be null");

		/* Put an element */
		((person *) dcontainer2.container)[0].age = 33;
		strcpy(((person *) dcontainer2.container)[0].name, "josh");
		ASSERT(dcontainer2.capacity >= 10, "The capacity should be 10");
		stl_free_container(dcontainer2.addr, dcontainer.capacity);
	}

	TEST(IsDynamic) {
		ASSERT(STL_IS_DYNAMIC_CONTAINER(dcontainer) == 1, "It should be true");
	}


	TEST(AssigningSTsize) {
		ASSERT(dcontainer.st_size == sizeof(stack), "IT should have this structure size");
	}

	stl_free_container(dcontainer.addr, dcontainer.capacity);	
} ENDTESTCASE



NEW_SUIT(SuitTestCon, InitStaticContainer, InitDynamicContainer);
