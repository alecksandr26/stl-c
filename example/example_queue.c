#include <stdio.h>
#include <string.h>
#include "../include/stl/queue.h"
#include "../include/stl/gen.h"

def_queue(float, 10);
def_dqueue(int);
def_dqueue(float);

def_queue(d_ptr(float), 100);
def_dqueue(d_ptr(float));


void print_attributes_queue_100(queue(d_ptr(float), 100) *queue) 
{ 
 	printf("size: %zu\n", st_size(*queue));
 	printf("capacity: %zu\n", st_capacity(*queue)); 
 	printf("rear: %i\n", queue->rear); 
 	printf("front: %i\n", queue->front); 
}

void print_attributes_queue_10(queue(float, 10) *queue)
{
	printf("size: %zu\n", st_size(*queue)); 
 	printf("capacity: %zu\n", st_capacity(*queue)); 
 	printf("rear: %i\n", queue->rear); 
 	printf("front: %i\n", queue->front);
}

void print_attributes_dqueue(dqueue(d_ptr(float)) *dqueue)
{
	printf("size: %zu\n", st_size(*dqueue)); 
 	printf("capacity: %zu\n", st_capacity(*dqueue));
 	printf("rear: %i\n", dqueue->rear); 
 	printf("front: %i\n", dqueue->front);
}

void print_attributes_queue(dqueue(int) *queue)
{
	printf("size: %zu\n", st_size(*queue)); 
 	printf("capacity: %zu\n", st_capacity(*queue)); 
 	printf("rear: %i\n", queue->rear); 
 	printf("front: %i\n", queue->front);
}

void example_static_queue_float(void)
{ 
 	queue(float, 10) queue;
	st_init(queue);


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
	st_init(queue);
	
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
	
	st_init(p_queue);

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
	
	st_init(p_queue);

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
	dqueue(d_ptr(float)) *dqueue = st_new(dqueue(d_ptr(float)));
	dst_init(*dqueue);
	
	float var = 1.0, var2 = 2.0, var3 = 3.0, var4 = 4.0, var5 = 5.0;
	
	queue_push(*dqueue, &var);
	queue_push(*dqueue, &var2);
	queue_push(*dqueue, &var3);
	queue_push(*dqueue, &var4);
	queue_push(*dqueue, &var5);
	
	(void) queue_pop(*dqueue);
	(void) queue_pop(*dqueue);
	/* (void) queue_pop(*dqueue); */
	
	print_attributes_dqueue(dqueue);

	printf("%f\n", *queue_front(*dqueue));
	printf("%f\n", *queue_back(*dqueue));
	
	printf("%f\n", *queue_pop(*dqueue));
	
	print_attributes_dqueue(dqueue);
	
	printf("%f\n", *queue_front(*dqueue));
	printf("%f\n", *queue_back(*dqueue));

	print_attributes_dqueue(dqueue);

	(void) queue_pop(*dqueue);
	
	printf("%f | %i\n", *queue_front(*dqueue), dqueue->front);
	printf("%f | %i\n", *queue_back(*dqueue), dqueue->rear);
	
	queue_push(*dqueue, &var);
	queue_push(*dqueue, &var2);

	queue_push(*dqueue, &var3);
	
	print_attributes_dqueue(dqueue);


	printf("%f\n", *queue_front(*dqueue));
	printf("%f\n", *queue_back(*dqueue));
	
		
	st_free(*dqueue);
}

int main() 
{
	dqueue(int) dq;
	dst_init(dq, 100);

	queue_push(dq, 10);
	queue_push(dq, 20);
	queue_push(dq, 30);
	queue_push(dq, 40);
	queue_push(dq, 50);
	
	(void) queue_pop(dq);
	(void) queue_pop(dq);
	(void) queue_pop(dq);

	printf("%i\n", queue_front(dq));
	printf("%i\n", queue_back(dq));

	print_attributes_queue(&dq);

	queue_push(dq, 10);

	printf("%i\n", queue_front(dq));
	printf("%i\n", queue_back(dq));

	print_attributes_queue(&dq);
	
	// example_dqueue_ptr_float();

	st_free(dq);
	
	return 0;
}




