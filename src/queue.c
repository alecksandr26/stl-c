#include <assert.h>
#include <stddef.h>
#include "../include/stl/queue.h"
#include "../include/stl/con.h"
#include "../include/stl/ex.h"

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

