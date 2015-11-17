#include "priority_queue.h"

void priority_queue_init(priority_queue_t *PQ)
{
	PQ->size = 0;
}

int priority_queue_empty(priority_queue_t *PQ)
{
	return (PQ->size == 0);
}

int parent(int i)
{
	return (i + 1) / 2 - 1;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

void exchange(int *a, int *b)
{
	int t = *a; *a = *b; *b = t;
}


void decrease_sift(priority_queue_t *PQ, int i)
{
	if (!(i < PQ->size)) return;

	int m = i;
	int p = 2 * i + 1;
	int q = 2 * i + 2;

	if (p < PQ->size && PQ->store[p] > PQ->store[m]) m = p;
	if (q < PQ->size && PQ->store[q] > PQ->store[m]) m = q;

	if (m != i) {
		exchange(&PQ->store[m], &PQ->store[i]);
		decrease_sift(PQ, m);
	}
}

void increase_sift(priority_queue_t *PQ, int i)
{
	if (i < 0) return;
	int p = (i + 1) / 2 - 1;
	if (p >= 0 && PQ->store[i] > PQ->store[p]) {
		exchange(&PQ->store[i], &PQ->store[p]);
		increase_sift(PQ, p);
	}
}


int priority_queue_insert(priority_queue_t *PQ, int *e)
{
	if (PQ->size + 1 > STORESIZE) return 0;
	PQ->store[PQ->size] = *e;
	PQ->size = PQ->size + 1;
	increase_sift(PQ, PQ->size-1);
	return 1;
}

int priority_queue_extract(priority_queue_t *PQ, int *e)
{
	if (PQ->size - 1 < 0) return 0;
	*e = PQ->store[0];
	exchange(&PQ->store[0], &PQ->store[PQ->size-1]);
	PQ->size = PQ->size - 1;
	decrease_sift(PQ, 0);
	return 1;
}


