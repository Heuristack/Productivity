#include "queue.h"

int enqueue(queue_t *Q, int *e)
{
	if (Q->size + 1 > STORESIZE) return 0;
	Q->store[Q->tail] = *e;
	Q->tail = (Q->tail + 1) % STORESIZE;
	Q->size = Q->size + 1;
	return 1;
}

int dequeue(queue_t *Q, int *e)
{
	if (Q->size - 1 < 0)  return 0;
	*e = Q->store[Q->head];
	Q->head = (Q->head + 1) % STORESIZE;
	Q->size = Q->size - 1;
	return 1;
}

void queue_init(queue_t *Q)
{
	Q->head = Q->tail = 0;
	Q->size = 0;
}

int queue_empty(queue_t *Q)
{
	return (Q->size == 0);
}
