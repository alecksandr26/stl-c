#include <stdio.h>
#include <string.h>
#include "../include/stl/queue.h"

def_queue(float, 10);
def_dqueue(float);

def_queue(d_ptr(float), 100);
def_dqueue(d_ptr(float));

void print_attributes_queue_100(queue(d_ptr(float), 100) *queue) 
{ 
 	printf("size: %zu\n", queue_size(*queue)); 
 	printf("capacity: %zu\n", queue_capacity(*queue)); 
 	printf("rear: %i\n", queue->rear); 
 	printf("front: %i\n", queue->front); 
}

void print_attributes_queue_10(queue(float, 10) *queue)
{
	printf("size: %zu\n", queue_size(*queue)); 
 	printf("capacity: %zu\n", queue_capacity(*queue)); 
 	printf("rear: %i\n", queue->rear); 
 	printf("front: %i\n", queue->front);
}

void print_attributes_dqueue(dqueue(d_ptr(float)) *dqueue)
{
	printf("size: %zu\n", queue_size(*dqueue)); 
 	printf("capacity: %zu\n", queue_capacity(*dqueue));
 	printf("rear: %i\n", dqueue->rear); 
 	printf("front: %i\n", dqueue->front);
}

void example_static_queue_float(void)
{ 
 	queue(float, 10) queue;
	queue_init(queue);


 	for (int i = 1; i <= 10; i++) 
 		queue_push(queue, (float) i); 

 	print_attributes_queue_10(&queue); 

	
 	printf("%f\n", queue_front(queue)); 
 	printf("%f\n", queue_pop(queue)); 
 	printf("%f\n", queue_front(queue)); 
	
 	print_attributes_queue_10(&queue); 

 	queue_push(queue, 2.0);
 	print_attributes_queue_10(&queue); 
 	printf("%f\n", queue_back(queue)); 
}


void example_static_queue_ptr_float(void)
{ 
	queue(d_ptr(float), 100) queue;
	queue_init(queue);
	
	print_attributes_queue_100(&queue);

	float var = 0.1, var2 = 2.5, var3 = 3.5;
	queue_push(queue, &var);
	queue_push(queue, &var2);
	queue_push(queue, &var3);

	print_attributes_queue_100(&queue);

	printf("%p\n", (void *) queue_front(queue));
	printf("%p\n", (void *) &var);
}


void example_abstra_data_types(void)
{	
	typedef struct {
		unsigned char age;
		char name[100];
	} person;

	def_queue(person);
	
	queue(person) p_queue;
	
	queue_init(p_queue);

	person p1 = { .age = 10, .name = "James"};
	person p2 = { .age = 12, .name = "Lois"};

	/* Push the data */
	
	queue_push(p_queue, p1);
	queue_push(p_queue, p2);

	p1.age = 0;
	strcpy(p1.name, "No more James");
	
	printf("%u | %s\n", queue_front(p_queue).age, queue_front(p_queue).name);
	printf("%u | %s\n", queue_back(p_queue).age, queue_back(p_queue).name);

	(void) queue_pop(p_queue);
	printf("%u | %s\n", queue_front(p_queue).age, queue_back(p_queue).name);
}


void example_abstra_data_types_ptr(void)
{	
	typedef struct {
		unsigned char age;
		char name[100];
	} person;

	def_queue(d_ptr(person));
	
	queue(d_ptr(person)) p_queue;
	
	queue_init(p_queue);

	person p1 = { .age = 10, .name = "James"};
	person p2 = { .age = 12, .name = "Lois"};

	/* Push the pointers */
	queue_push(p_queue, &p1);
	queue_push(p_queue, &p2);

	p1.age = 0;
	strcpy(p1.name, "No more James");
	
	printf("%u | %s\n", queue_front(p_queue)->age, queue_front(p_queue)->name);
	printf("%u | %s\n", queue_back(p_queue)->age, queue_back(p_queue)->name);

	(void) queue_pop(p_queue);
	
	printf("%u | %s\n", queue_front(p_queue)->age, queue_back(p_queue)->name);
}


void example_dqueue_ptr_float(void)
{
	dqueue(d_ptr(float)) *dqueue = new_dqueue(d_ptr(float));
	dqueue_init(dqueue);

	float var = 1.0, var2 = 2.0, var3 = 3.0, var4 = 4.0, var5 = 5.0;
	
	dqueue_push(dqueue, &var);
	dqueue_push(dqueue, &var2);
	dqueue_push(dqueue, &var3);
	dqueue_push(dqueue, &var4);
	dqueue_push(dqueue, &var5);
	
	(void) dqueue_pop(dqueue);
	(void) dqueue_pop(dqueue);
	(void) dqueue_pop(dqueue);
	
	print_attributes_dqueue(dqueue);

	printf("%f\n", *dqueue_front(dqueue));
	printf("%f\n", *dqueue_back(dqueue));

	printf("%f\n", *dqueue_pop(dqueue));
	
	print_attributes_dqueue(dqueue);
	
	printf("%f\n", *dqueue_front(dqueue));
	printf("%f\n", *dqueue_back(dqueue));

	(void) dqueue_pop(dqueue);
	
	dqueue_push(dqueue, &var);
	dqueue_push(dqueue, &var2);

	dqueue_push(dqueue, &var3);

	print_attributes_dqueue(dqueue);


	printf("%f\n", *dqueue_front(dqueue));
	printf("%f\n", *dqueue_back(dqueue));
	
		
	stl_free(dqueue);
}


int main() 
{

	
	
	return 0;
}




