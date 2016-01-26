#ifndef queue_h
#define queue_h

#define STORESIZE 0x400

typedef struct queue {
	int store[STORESIZE];
	int head;			// get index (index_get)
	int tail;			// put index (index_put)
	int size;
} queue_t;

void queue_init(queue_t *Q);
int queue_empty(queue_t *Q);

int enqueue(queue_t *Q, int *e);
int dequeue(queue_t *Q, int *e);

#endif
