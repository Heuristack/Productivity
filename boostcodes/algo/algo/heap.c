#include "heap.h"

void exchange(int *a, int *b)
{
	int t = *a; *a = *b; *b = t;
}

int parent(int i)
{
	return i/2;
}

int left(int i)
{
	return 2*i;
}

int right(int i)
{
	return 2*i + 1;
}

int initheapstore(heap_t *H, int A[], int n)
{
	if (n > STORESIZE) return -1;
	for (int i = 0; i < n; i++)
		H->store[i+1] = A[i];
	H->length = n;
	H->heap_size = 0;
	return n;
}

void printheapstore(heap_t *H)
{
	for (int i = 1; i <= H->length; i++)
		printf("[%02d:%02d] ", i, H->store[i]);
	printf("\n");
}

void printheap(heap_t *H, int i)
{
	if (i > H->heap_size) return;
	printf("[%02d:%02d] ", i, H->store[i]);
	printheap(H, left(i));
	printheap(H, right(i));
}

void max_heapify(heap_t *H, int i)
{
	if (i > H->heap_size) return;

	int m = i;
	int p = left(i);
	int q = right(i);

	if (p <= H->heap_size && H->store[p] > H->store[m]) m = p;
	if (q <= H->heap_size && H->store[q] > H->store[m]) m = q;
	if (m != i) {
		exchange(&H->store[m], &H->store[i]);
		max_heapify(H, m);
	}
}

void build_max_heap(heap_t *H)
{
	H->heap_size = H->length;
	int n = H->length / 2;
	for (int i = n; i >= 1; i--) {
		max_heapify(H, i);
	}
}

void sort_heap(heap_t *H)
{
	while (H->heap_size > 1) {
		exchange(&H->store[1], &H->store[H->heap_size--]);
		max_heapify(H, 1);
	}
}

