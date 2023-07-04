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

int main(void)
{
	list(float) list;
	list_init(list);

	puts("\nInitial list");
	list_append(list, 1.0);
	list_append(list, 2.0);
	list_append(list, 3.0);
	list_append(list, 4.0);
	list_append(list, 5.0);
	list_append(list, 6.0);
	list_append(list, 7.0);
	list_append(list, 8.0);
	
	print_float_list(&list); // list: 1, 2, 3, 4, 5, 6, 7, 8
	print_list_attributes(&list);

	puts("\nRemoving element");
	(void) list_pop(list);
	
	print_float_list(&list); /* list: 1, 2, 3, 4, 5, 6, 7 */
	(void) list_erase(list, 1);
	print_list_attributes(&list);
	
	print_float_list(&list); /* list: 1, 3, 4, 5, 6, 7 */
	(void) list_erase(list, 2);
	print_float_list(&list); /* list: 1, 3, 5, 6, 7 */
	print_list_attributes(&list);


	puts("\nAfter pushing");
	puts("Pushing the 9.0");
	list_append(list, 9.0);
	puts("Pushing the 10.0");
	list_append(list, 10.0);
	print_float_list(&list); /* list: 1, 3, 5, 6, 7, 9, 10 */
	
	print_list_attributes(&list);
	
	puts("\nAftert inserting elements");
	puts("Inserting the 11.0 at 0");
	list_insert(list, 11.0, 0);
	
	print_float_list(&list); /* list: 11, 1, 3,  5, 6, 7, 9, 10 */
	
	puts("Inserting the 12.0 at 0");
	list_insert(list, 12.0, 0);
	print_float_list(&list); /* list: 12, 11, 1, 3, 5, 6, 7, 9, 10 */
	
	print_list_attributes(&list);
		
	return 0;
}

