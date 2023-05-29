#include <except.h>

Except NotEnoughCapacity = {"NotEnoughCapacity: Not enough capacity in the structure"};
Except EmptyStructure = {"EmptyStructure: The structure is empty, it doesn't have any element"};
Except NotEnoughMemory = {"NotEnoughMemory: Not enough memory for a new structure allocation"};
Except NotEnoughMemoryToRealloc =					\
	{"NotEnoughMemoryToRealloc: Not enough memory for a reallocation of the container"};
