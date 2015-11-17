#include "queue.h"

int main()
{
	int A[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	int n = sizeof(A)/sizeof(int);

	queue_t Q;
	queue_init(&Q);
	for (int i = 0; i < n; i++)
		if (!enqueue(&Q, &A[i])) break;

	for (int e = 0; !queue_empty(&Q); printf("%d ", e))
		if (!dequeue(&Q, &e)) break;
	printf("\n");
}
