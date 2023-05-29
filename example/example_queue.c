#include <stdio.h>
#include "../include/stl/queue.h"

/* def_queue(float, 10); */
/* def_queue(float); */

/* def_dqueue(float); */
def_queue(stl_ptr(float), 100);
def_dqueue(stl_ptr(float));

void print_attributes(queue(stl_ptr(float), 100) *queue) 
{ 
 	printf("size: %zu\n", queue_size(*queue)); 
 	printf("capacity: %zu\n", queue_capacity(*queue)); 
 	printf("rear: %i\n", queue->rear); 
 	printf("front: %i\n", queue->front); 
}


/* void example_static_queue_float(void) */
/* { */
/* 	queue(float, 10) queue; */
/* 	queue_init(queue); */


/* 	for (int i = 1; i <= 10; i++) */
/* 		queue_push(queue, (float) i); */

/* 	print_attributes(&queue); */

	
/* 	printf("%f\n", queue_front(queue)); */
/* 	printf("%f\n", queue_pop(queue)); */
/* 	printf("%f\n", queue_front(queue)); */
	
/* 	print_attributes(&queue); */

/* 	queue_push(queue, 2.0); */
/* 	print_attributes(&queue); */
/* 	printf("%f\n", queue_back(queue)); */
/* } */


int main() 
{
	queue(stl_ptr(float), 100) queue;
	queue_init(queue);
	
	print_attributes(&queue);

	float var = 0.1, var2 = 2.5, var3 = 3.5;
	queue_push(queue, &var);
	queue_push(queue, &var2);
	queue_push(queue, &var3);

	print_attributes(&queue);

	printf("%p\n", (void *) queue_front(queue));
	printf("%p\n", (void *) &var);

	dqueue(stl_ptr(float)) *dqueue = new_dqueue(stl_ptr(float), 100);
	dqueue_init(dqueue);

	
	stl_free(dqueue);

	/* queue_init(queue); */

	/* Person p1 = { .age = 10, .name = "James"}; */

	/* queue_push(queue, p1); */

	/* p1.age = 0; */

	/* printf("%u | %s\n", queue_front(queue).age, queue_front(queue).name); */
	
	
	return 0;
}




