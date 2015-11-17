#include "sorting.h"

void sortbycountingbackward(int A[], int n)
{
	static int k = 0xffffffff;
	int *count = (int *) malloc(sizeof(int) * k);
	for (int i = 1; i < k; i++) count[i] = 0;

	// count frequencies and compute final order (position)
	for (int i = 0; i < n; i++) count[A[i]] += 1;
	for (int i = 1; i < k; i++) count[i] += count[i-1];

	int *T = (int *) malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) T[i] = A[i];

	// place element by final position stored in count
	for (int i = n-1; i >= 0; i--) A[--count[T[i]]] = T[i];

	free(T); free(count);
} //runtime: O(n+k)

// counting sort: [key-indexed counting] from [Algo4.Sedgewick]
void sortbycounting(int A[], int n, int k)
{
	// static int k = 0xffffffff;
	int *count = (int *) malloc(sizeof(int) * k);
	for (int i = 1; i < k; i++) count[i] = 0;

	// count frequencies and compute final order (position)
	for (int i = 0; i < n; i++) count[A[i]+1] += 1;
	for (int i = 1; i < k; i++) count[i] += count[i-1];

	int *T = (int *) malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) T[i] = A[i];

	// place element by using final position stored in count
	for (int i = 0; i < n; i++) A[count[T[i]]++] = T[i];

	free(T); free(count);
} // runtime: O(n+k)

// counting sort:
void countingsort(int A[], int n)
{
	int k = 0x100;
	sortbycounting(A,n,k);
}

// Least Significant Digit First (LSD) Radix Sort:
void byteradixsort(int A[], int n)
{
	int d = 0x4;		// one integer consists of 4 bytes (radices)
	int k = 0x100;		// range for one byte (radix): 0..255 (0xff)

	int *count = (int *) malloc(sizeof(int) * k);
	int *T = (int *) malloc(sizeof(int) * n);
	for (int r = 0; r < d; r++) { // for little-endian machine
		// initialize count to zero
		for (int i = 0; i < k; i++) count[i] = 0;
		// count frequencies and compute final order (position)
		for (int i = 0; i < n; i++) count[*(((char *)(&A[i]))+r)+1] += 1;
		for (int i = 0; i < k; i++) count[i] += count[i-1];
		// place element by using final position stored in count
		for (int i = 0; i < n; i++) T[i] = A[i];
		for (int i = 0; i < n; i++) A[count[*(((char *)(&T[i]))+r)]++] = T[i];
	}
	free(T); free(count);
} // runtime: O(d(n+k))

