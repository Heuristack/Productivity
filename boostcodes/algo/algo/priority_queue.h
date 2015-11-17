#ifndef priority_queue_h
#define priority_queue_h

#define STORESIZE 0x400

typedef struct priority_queue {
	int store[STORESIZE];
	int size;
} priority_queue_t;


void priority_queue_init(priority_queue_t *PQ);
int priority_queue_empty(priority_queue_t *PQ);

int priority_queue_insert(priority_queue_t *PQ, int *e);
int priority_queue_extract(priority_queue_t *PQ, int *e);

#endif
