#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "../include/stl/queue.h"
#include "../include/stl/con.h"
#include "../include/stl/ex.h"


#define MIN(a, b) ((a > b) ? b : a)
#define MAX(a, b) ((a > b) ? a : b)

size_t stl_queue_front(__stl_queue_t *queue)
{
	assert(queue != NULL && "Can't be null");

	if (queue_size(*queue) == 0)
		throw_except(EmptyStructure);
	
	return (size_t) queue->front;
}

size_t stl_queue_back(__stl_queue_t *queue)
{
	assert(queue != NULL && "Can't be null");

	if (queue_size(*queue) == 0)
		throw_except(EmptyStructure);
	
	return (size_t) queue->rear;
}

size_t stl_queue_inc(__stl_queue_t *queue)
{
	assert(queue != NULL && "Can't be null");
	
	if (queue_size(*queue) == 0)
		queue->front = 0;

	queue->rear++;

	if ((queue->front == 0 && queue->rear == (int) queue_capacity(*queue)) 
	    || (queue->front != 0 && queue->rear == queue->front))
		throw_except(NotEnoughCapacity);
	
	queue->rear %= queue_capacity(*queue);
	queue->size++;
	return (size_t) queue->rear;
}

size_t stl_queue_dec(__stl_queue_t *queue)
{
	assert(queue != NULL && "Can't be null");
	
	if (queue_size(*queue) == 0)
		throw_except(EmptyStructure);

	const size_t front = (size_t) queue->front;

	if (queue->front == queue->rear)
		queue->front = queue->rear = -1;
	else
		queue->front = (queue->front + 1) % queue_capacity(*queue);
	queue->size--;
	return front;
}


unsigned char *stl_dqueue_inc(__stl_queue_t *dqueue)
{
	assert(dqueue != NULL && "Can't be null");
	
	if (queue_size(*dqueue) == 0)
		dqueue->front = 0;

	dqueue->rear++;

	if ((dqueue->front == 0 && dqueue->rear == (int) queue_capacity(*dqueue))
	    || (dqueue->front != 0 && dqueue->rear == dqueue->front)) {
		stl_realloc_container((unsigned char *) dqueue, sizeof(*dqueue), dqueue->con.capacity \
				      * STL_DEFAULT_DQUEUE_INCREASE_RATE * dqueue->con.dtype_size);
		if (dqueue->rear == dqueue->front) {
			size_t min = MIN((size_t) dqueue->rear, dqueue->con.capacity - dqueue->front);
			size_t max = MAX((size_t) dqueue->rear, dqueue->con.capacity - dqueue->front);
			
			unsigned char temp_buff[min];
			unsigned char *min_addr = ((size_t) dqueue->rear 
						   > dqueue->con.capacity - dqueue->front)
				? dqueue->con.container
				: dqueue->con.container + (dqueue->rear * dqueue->con.dtype_size);

			unsigned char *max_addr = ((size_t) dqueue->rear
						   > dqueue->con.capacity - dqueue->front)
				? dqueue->con.container + (dqueue->rear * dqueue->con.dtype_size)
				: dqueue->con.container;
			
			/* Swap the pieces */
			memcpy(temp_buff, min_addr, min);
			memcpy(dqueue->con.container, max_addr, max);
			memcpy(max_addr, temp_buff, min);

			dqueue->front = 0;
			dqueue->rear = dqueue->con.capacity;
		}
		
		STL_INIT_D_CONTAINER_CAPACITY(dqueue->con);
	}
		
	
	dqueue->rear %= queue_capacity(*dqueue);
	dqueue->size++;
	return dqueue->con.container + (dqueue->rear * dqueue->con.dtype_size);
}


unsigned char *stl_dqueue_dec(__stl_queue_t *queue)
{
	assert(queue != NULL && "Can't be null");
	
	if (queue_size(*queue) == 0)
		throw_except(EmptyStructure);

	const size_t front = (size_t) queue->front;

	if (queue->front == queue->rear)
		queue->front = queue->rear = -1;
	else
		queue->front = (queue->front + 1) % queue_capacity(*queue);
	
	queue->size--;
	return queue->con.container + (front * queue->con.dtype_size);
}

