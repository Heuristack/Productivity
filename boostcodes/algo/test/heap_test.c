#include "algo.h"
#include "heap.h"

int main()
{
	int A[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	int n = sizeof(A)/sizeof(int);
	heap_t H;
	initheapstore(&H, A, n);
	printheapstore(&H);
	build_max_heap(&H);
	printheapstore(&H);
	printheap(&H,1);
	printf("\n");
	sort_heap(&H);
	printheapstore(&H);
}
