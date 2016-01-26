#include "stack.h"

int main()
{
	int A[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	int n = sizeof(A)/sizeof(int);

	stack_t S;
	stack_init(&S);
	for (int i = 0; i < n; i++)
		if (!push(&S, &A[i])) break;

	for (int e = 0; !stack_empty(&S); printf("%d ", e))
		if (!pop(&S, &e)) break;
	printf("\n");
}
