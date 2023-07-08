#include <stdio.h>

#include "../include/stl/list.h"
#include "../include/stl/gen.h"
#include "../include/stl/ex.h"


def_list(float);

void print_list_attributes(list(float) *list)
{
	printf("size_st: %zu\n", st_size(list->pind_deleted));
	printf("size: %zu\n", st_size(*list));
	printf("size_con: %zu\n", list->size_con);
	printf("size_ul: %zu\n", list->size_ul);
	printf("capacity: %zu\n", st_capacity(*list));
	printf("empty: %s\n", st_empty(*list) ? "True" : "False");
	
}

void print_float_list(list(float) *list)
{
	for (size_t i = 0; i < st_size(*list); i++) {
		printf("%f", list_index(*list, i));
		if (i < st_size(*list) - 1)
			printf(", ");
	}
	putchar('\n');
}

int main(void)
{
	list(float) list;
	st_init(list);

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

	puts("\nAfter pushing");
	puts("Pushing the 13.0");
	list_append(list, 13.0);
	puts("Pushing the 14.0");
	list_append(list, 14.0);
	print_float_list(&list); /* list: 1, 3, 5, 6, 7, 9, 10, 13, 14 */
	
	print_list_attributes(&list);


	puts("\nAftert inserting elements");
	printf("Inserting the 20.0 at %zu\n", st_size(list) - 2);
	list_insert(list, 20.0, st_size(list) - 2);
	
	print_float_list(&list); /* list: 1, 3, 5, 6, 7, 9, 10, 20, 13, 14 */
	
	printf("Inserting the 21.0 at %zu\n", st_size(list) - 1);
	list_insert(list, 21.0, st_size(list) - 1);
	print_float_list(&list); /* list: 1, 3, 5, 6, 7, 9, 10, 20, 13, 21, 14 */

		
	return 0;
}

