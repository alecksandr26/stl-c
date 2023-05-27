#include <unittest.h>
#include <malloc.h>
#include <string.h>
#include "../include/stl/con.h"

TESTCASE(InitStaticContainer) {
	typedef struct  {
		int age;
		char name[100];
	} person;

	typedef struct {
		size_t head;
	} stack;
	
	TEST(InitStatic) {
		STL_CONTAINER(float, 10) container; /* Create the container */
		STL_INIT_D_CONTAINER_DTYPE_SIZE(container, float);
		STL_INIT_D_CONTAINER_CAPACITY(container);

		ASSERT(sizeof(container.container) >= 10 * sizeof(float),
		       "It shold create the frame of that size");
	}

	TEST(InitStaticStruct) {
		STL_CONTAINER(person, 10) container; /* Create the container */
		STL_INIT_D_CONTAINER_DTYPE_SIZE(container, float);
		STL_INIT_D_CONTAINER_CAPACITY(container);
		
		ASSERT(sizeof(container.container) >= 10 * sizeof(person));
		ASSERT(container.capacity >= 10, "The capacity should be 10");
	}

	TEST(IsStatic) {
		STL_CONTAINER(float, 10) container; /* Create the container */
		ASSERT(__STL_IS_DYNAMIC_CONTAINER(container.container) == 0, "It should be false");
	}

	TEST(AssigningSTsize) {
		STL_CONTAINER(float, 10) container; /* Create the container */
		STL_INIT_D_CONTAINER_ST_SIZE(container, stack);

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

	STL_DCONTAINER(float) dcontainer; /* Create the dynamic container */

	/* Alloc memory */
	if ((dcontainer.container = malloc(sizeof(float) * 10)) == NULL) {
		fprintf(stderr, "Error running the testcase");
		abort();
	}

	stl_heapaddr = ((unsigned long) dcontainer.container) + (sizeof(float) * 10);
	
	TEST(InitDynamic) {
		STL_INIT_D_CONTAINER_DTYPE_SIZE(dcontainer, float);
		STL_INIT_D_CONTAINER_CAPACITY(dcontainer);
		ASSERT(dcontainer.capacity >= 10,
		       "It shold create the frame of that size");
	}

	TEST(InitDynamicStruct) {
		STL_DCONTAINER(person) dcontainer2; /* Create the dynamic container */
		
		/* Alloc memory */
		if ((dcontainer2.container = malloc(sizeof(person) * 10)) == NULL) {
			fprintf(stderr, "Error running the testcase");
			abort();
		}

		stl_heapaddr = ((unsigned long) dcontainer2.container) + (sizeof(person) * 10);

		ASSERT(dcontainer2.container != NULL, "Shouldn't be null");

		STL_INIT_D_CONTAINER_DTYPE_SIZE(dcontainer2, person);
		STL_INIT_D_CONTAINER_CAPACITY(dcontainer2);

		/* Put an element */
		((person *) dcontainer2.container)[0].age = 33;
		strcpy(((person *) dcontainer2.container)[0].name, "josh");
		ASSERT(dcontainer2.capacity >= 10, "The capacity should be 10");
		stl_heapaddr = ((unsigned long) dcontainer2.container);
		free(dcontainer2.container);
	}

	TEST(IsDynamic) {
		ASSERT(__STL_IS_DYNAMIC_CONTAINER(dcontainer.container) == 1, "It should be true");
	}


	TEST(AssigningSTsize) {
		STL_INIT_D_CONTAINER_ST_SIZE(dcontainer, stack);

		ASSERT(dcontainer.st_size == sizeof(stack), "IT should have this structure size");
	}

	stl_heapaddr = ((unsigned long) dcontainer.container);

	/* Free the structure */
	free(dcontainer.container);

} ENDTESTCASE





NEW_SUIT(SuitTestCon, InitStaticContainer, InitDynamicContainer);
