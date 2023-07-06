#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "../include/stl/queue.h"
#include "../include/stl/con.h"
#include "../include/stl/ex.h"
#include "../include/stl/gen.h"


#define MIN(a, b) ((a > b) ? b : a)
#define MAX(a, b) ((a > b) ? a : b)

size_t __stl_queue_front(__stl_queue_t *queue)
{
	assert(queue != NULL && "Can't be null");

	if (st_size(*queue) == 0)
		throw(EmptyStructure);
	
	return (size_t) queue->front;
}

size_t __stl_queue_back(__stl_queue_t *queue)
{
	assert(queue != NULL && "Can't be null");

	if (st_size(*queue) == 0)
		throw(EmptyStructure);
	
	return (size_t) queue->rear - 1;
}

unsigned char *__stl_queue_inc(__stl_queue_t *queue)
{
	assert(queue != NULL && "Can't be null");
	
	if (st_size(*queue) == 0)
		queue->front = 0;

	queue->rear++;

	if ((queue->front == 0 && queue->rear == (int) st_capacity(*queue))
	    || (queue->front != 0 && queue->rear - 1 == queue->front)) {
		if (queue->con.type == STL_STATIC)
			throw(NotEnoughCapacity);
		
		queue->con.container = queue->con.addr
			= stl_realloc_container((unsigned char *) queue->con.container,
						queue->con.capacity
						* STL_DEFAULT_DQUEUE_INCREASE_RATE
						* queue->con.dtype_size);

		if (queue->rear == queue->front) {
			size_t min = MIN((size_t) queue->rear, queue->con.capacity - queue->front);
			size_t max = MAX((size_t) queue->rear, queue->con.capacity - queue->front);
			

			unsigned char *min_addr = ((size_t) queue->rear 
						   > queue->con.capacity - queue->front)
				? queue->con.addr + (queue->rear * queue->con.dtype_size)
				: queue->con.addr;

			unsigned char *max_addr = ((size_t) queue->rear
						   > queue->con.capacity - queue->front)
				? queue->con.addr
				: queue->con.addr + (queue->rear * queue->con.dtype_size);

			/* Dump the smallest piece in the buffer */
			unsigned char temp_buff[min * queue->con.dtype_size];
			memcpy(temp_buff, min_addr, min * queue->con.dtype_size);

			if (min == (size_t) queue->rear) {
				memcpy(queue->con.addr, max_addr,
				       max * queue->con.dtype_size); /* front piece */
				memcpy(queue->con.addr /* rear piece */
				       + (max * queue->con.dtype_size), temp_buff,
				       min * queue->con.dtype_size);
			} else {
				for (int i = queue->rear - 1; i > -1; i--)
					memcpy(queue->con.addr + ((i + min) * queue->con.dtype_size),
					       queue->con.addr + (i * queue->con.dtype_size),
					       queue->con.dtype_size); /* rear piece */
				memcpy(queue->con.addr, min_addr,
				       min * queue->con.dtype_size); /* front piece */
			}
			queue->front = 0;
			queue->rear = queue->con.capacity;
		}
		
		queue->con.capacity *= STL_DEFAULT_DQUEUE_INCREASE_RATE;
	}
	
	queue->rear %= st_capacity(*queue);
	queue->con.size++;
	return queue->con.addr + ((size_t) queue->rear - 1) * queue->con.dtype_size;
}

unsigned char *__stl_queue_dec(__stl_queue_t *queue)
{
	assert(queue != NULL && "Can't be null");
	
	if (st_size(*queue) == 0)
		throw(EmptyStructure);
	
	if (queue->con.type == STL_DYNAMIC
	    && queue->con.size <= queue->con.capacity / STL_DEFAULT_DQUEUE_INCREASE_RATE) {
		if (queue->front <= queue->rear) {
			memcpy(queue->con.addr, queue->con.addr
			       + (queue->front * queue->con.dtype_size),
			       queue->con.size * queue->con.dtype_size);
		} else {
			size_t min = MIN((size_t) queue->rear + 1, queue->con.size - queue->front);
			size_t max = MAX((size_t) queue->rear + 1, queue->con.size - queue->front);
			unsigned char *min_addr = ((size_t) queue->rear + 1
						   > queue->con.capacity - queue->front)
				? queue->con.addr + (queue->rear * queue->con.dtype_size)
				: queue->con.addr;

			unsigned char *max_addr = ((size_t) queue->rear + 1
						   > queue->con.capacity - queue->front)
				? queue->con.addr
				: queue->con.addr + (queue->rear * queue->con.dtype_size);
			
			unsigned char temp_buff[min * queue->con.dtype_size];
			memcpy(temp_buff, min_addr, min * queue->con.dtype_size);

			if (min == (size_t) queue->rear + 1) {
				memcpy(queue->con.addr, max_addr,
				       max * queue->con.dtype_size); /* front piece */
				memcpy(queue->con.addr /* rear piece */
				       + (max * queue->con.dtype_size), temp_buff,
				       min * queue->con.dtype_size);
			} else {
				for (int i = queue->rear - 1; i > -1; i--)
					memcpy(queue->con.addr + ((i + min) * queue->con.dtype_size),
					       queue->con.addr + (i * queue->con.dtype_size),
					       queue->con.dtype_size); /* rear piece */
				memcpy(queue->con.addr, min_addr,
				       min * queue->con.dtype_size); /* front piece */
			}
		}
		
		queue->front = 0;
		queue->rear = queue->con.size;
		
		queue->con.container = queue->con.addr
			= stl_realloc_container(queue->con.addr,
						(queue->con.size + 1) * queue->con.dtype_size);
		queue->con.capacity = queue->con.size + 1;
	}

	const size_t front = (size_t) queue->front;
	
	if (queue->front == queue->rear - 1) {
		queue->front = queue->rear = 0;
	} else
		queue->front = (queue->front + 1) % st_capacity(*queue);

	queue->con.size--;
	return queue->con.addr + ((front) * queue->con.dtype_size);
}

