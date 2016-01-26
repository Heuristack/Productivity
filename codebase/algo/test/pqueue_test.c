#include "priority_queue.h"

int main()
{
	int A[] = { 16, 14, 10, 8, 7, 9, 5, 3000, 3, 2, 4, 1, 20, 18 };
	int n = sizeof(A)/sizeof(int);

	priority_queue_t PQ;
	priority_queue_init(&PQ);

	for (int i = 0; i < n; i++)
		priority_queue_insert(&PQ, &A[n-1-i]);

	for (int e = 0; !priority_queue_empty(&PQ); printf("%d ", e))
		if (!priority_queue_extract(&PQ, &e)) break;
	printf("\n");
}
