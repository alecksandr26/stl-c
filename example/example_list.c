#include <stdio.h>

#include "../include/stl/list.h"
#include "../include/stl/ex.h"

def_list(float);

void print_list_attributes(list(float) *list)
{
	printf("size_st: %zu\n", stack_size(*list->st));
	printf("size: %zu\n", list_size(*list));
	printf("size_con: %zu\n", list->size_con);
	printf("size_ul: %zu\n", list->size_ul);
	printf("capacity: %zu\n", list_capacity(*list));
	printf("empty: %s\n", list_empty(*list) ? "True" : "False");
	
}


void print_float_list(list(float) *list)
{
	for (size_t i = 0; i < list_size(*list); i++) {
		printf("%f", list_index(*list, i));
		if (i < list_size(*list) - 1)
			printf(", ");
	}
	putchar('\n');
}

int foo(int *ptr) {
	return *ptr = 10;
}

int main(void)
{
	list(float) list;
	list_init(list);
	
	list_append(list, 1.0); // list: 1
	list_append(list, 2.0); // list: 1, 2
	list_append(list, 3.0); // list: 1, 2, 3
	list_append(list, 4.0); // list: 1, 2, 3, 4
	list_append(list, 5.0); // list: 1, 2, 3, 4, 5
	list_append(list, 6.0); // list: 1, 2, 3, 4, 5, 6
	list_append(list, 7.0); // list: 1, 2, 3, 4, 5, 6, 7
	list_append(list, 8.0); // list: 1, 2, 3, 4, 5, 6, 7, 8

	puts("\nInitial list");
	print_float_list(&list);
	print_list_attributes(&list);
	
	puts("\nAfer two deletions");
	(void) list_erase(list, 1); // list: 1, 3, 4, 5, 6, 7, 8
	print_float_list(&list);
	(void) list_erase(list, 2); // list: 1, 3, 5, 6, 7, 8
	print_float_list(&list);
	print_list_attributes(&list);

	puts("\nAfer pushing two elements");
	list_append(list, 2.0); // list: 1, 3, 5, 6, 7, 8, 2
	print_float_list(&list);
	list_append(list, 4.0); // list: 1, 3, 5, 6, 7, 8, 2, 4
	print_float_list(&list);
	print_list_attributes(&list);

	puts("\nAfer removing two elements");
	(void) list_pop(list); // list: 1, 3, 5, 6, 7, 8, 2
	print_float_list(&list);
	(void) list_erase(list, 2); // list: 1, 3, 6, 7, 8, 2
	print_float_list(&list);
	print_list_attributes(&list);

	puts("\nAfer inserting two elements");
	list_insert(list, 10.0, 0);
	print_float_list(&list);
	print_list_attributes(&list);

	
	return 0;
}

