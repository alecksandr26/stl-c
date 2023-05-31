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
			

			unsigned char *min_addr = ((size_t) dqueue->rear 
						   > dqueue->con.capacity - dqueue->front)
				? dqueue->con.container + (dqueue->rear * dqueue->con.dtype_size)
				: dqueue->con.container;

			unsigned char *max_addr = ((size_t) dqueue->rear
						   > dqueue->con.capacity - dqueue->front)
				? dqueue->con.container
				: dqueue->con.container + (dqueue->rear * dqueue->con.dtype_size);

			/* Dump the smallest piece in the buffer */
			unsigned char temp_buff[min * dqueue->con.dtype_size];
			memcpy(temp_buff, min_addr, min * dqueue->con.dtype_size);

			if (min == (size_t) dqueue->rear) {
				memcpy(dqueue->con.container, max_addr,
				       max * dqueue->con.dtype_size); /* front piece */
				memcpy(dqueue->con.container /* rear piece */
				       + (max * dqueue->con.dtype_size), temp_buff,
				       min * dqueue->con.dtype_size);
			} else {
				for (int i = dqueue->rear - 1; i > -1; i--)
					memcpy(dqueue->con.container + ((i + min) * dqueue->con.dtype_size),
					       dqueue->con.container + (i * dqueue->con.dtype_size),
					       dqueue->con.dtype_size); /* rear piece */
				memcpy(dqueue->con.container, min_addr,
				       min * dqueue->con.dtype_size); /* front piece */
			}
			dqueue->front = 0;
			dqueue->rear = dqueue->con.capacity;
		}
		
		STL_INIT_D_CONTAINER_CAPACITY(dqueue->con);
	}
		
	
	dqueue->rear %= queue_capacity(*dqueue);
	dqueue->size++;
	return dqueue->con.container + (dqueue->rear * dqueue->con.dtype_size);
}


unsigned char *stl_dqueue_dec(__stl_queue_t *dqueue)
{
	assert(dqueue != NULL && "Can't be null");
	
	if (queue_size(*dqueue) == 0)
		throw_except(EmptyStructure);

	if (dqueue->size <= dqueue->con.capacity / STL_DEFAULT_DQUEUE_INCREASE_RATE) {
		if (dqueue->front <= dqueue->rear) {
			memcpy(dqueue->con.container, dqueue->con.container
			       + (dqueue->front * dqueue->con.dtype_size),
			       dqueue->size * dqueue->con.dtype_size);
		} else {
			size_t min = MIN((size_t) dqueue->rear + 1, dqueue->size - dqueue->front);
			size_t max = MAX((size_t) dqueue->rear + 1, dqueue->size - dqueue->front);
			unsigned char *min_addr = ((size_t) dqueue->rear + 1
						   > dqueue->con.capacity - dqueue->front)
				? dqueue->con.container + (dqueue->rear * dqueue->con.dtype_size)
				: dqueue->con.container;

			unsigned char *max_addr = ((size_t) dqueue->rear + 1
						   > dqueue->con.capacity - dqueue->front)
				? dqueue->con.container
				: dqueue->con.container + (dqueue->rear * dqueue->con.dtype_size);
			
			unsigned char temp_buff[min * dqueue->con.dtype_size];
			memcpy(temp_buff, min_addr, min * dqueue->con.dtype_size);

			if (min == (size_t) dqueue->rear + 1) {
				memcpy(dqueue->con.container, max_addr,
				       max * dqueue->con.dtype_size); /* front piece */
				memcpy(dqueue->con.container /* rear piece */
				       + (max * dqueue->con.dtype_size), temp_buff,
				       min * dqueue->con.dtype_size);
			} else {
				for (int i = dqueue->rear - 1; i > -1; i--)
					memcpy(dqueue->con.container + ((i + min) * dqueue->con.dtype_size),
					       dqueue->con.container + (i * dqueue->con.dtype_size),
					       dqueue->con.dtype_size); /* rear piece */
				memcpy(dqueue->con.container, min_addr,
				       min * dqueue->con.dtype_size); /* front piece */
			}
			
		}
		dqueue->front = 0;
		dqueue->rear = dqueue->size - 1;
		stl_realloc_container((unsigned char *) dqueue,
				      sizeof(*dqueue),
				      dqueue->size * dqueue->con.dtype_size);
		STL_INIT_D_CONTAINER_CAPACITY(dqueue->con);
	}

	const size_t front = (size_t) dqueue->front;

	if (dqueue->front == dqueue->rear)
		dqueue->front = dqueue->rear = -1;
	else
		dqueue->front = (dqueue->front + 1) % queue_capacity(*dqueue);

	dqueue->size--;
	return dqueue->con.container + (front * dqueue->con.dtype_size);
}

