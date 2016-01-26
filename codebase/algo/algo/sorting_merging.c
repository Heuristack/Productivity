#include "sorting.h"

/**
 * Sort by Merging
 *
 * merging(collating): combine multiple ordered sets into one ordered set
 * as opposite to
 * distribution
 *
 *
 *
**/


// merge: merge 2 sorted arrays A[p..m] and A[m+1..q] into A[p..q]
void merge(int A[], int p, int m, int q)
{
	int k = 0;
	int n = q - p + 1;
	int i = p;
	int j = m + 1;
	int *B = (int *) malloc(sizeof(int) * n);

	while ((i <= m) && (j <= q)) {
		B[k++] = (A[i] < A[j]) ? A[i++] : A[j++];
	} //invariant: A[0..k] in final position
	int r = (i <= m) ? i : j;
	while (k < n) {
		B[k++] = A[r++];
	} //invariant: A[0..k] in final position

	for (k = 0; k < n; k++) {
		A[p+k] = B[k];
	} //invariant: A[p..p+k] and B[0..k] are same

	free(B);
} //runtime: O(n)

// mergesort: A[p..q] = merge(mergesort(A[p..m]), mergesort(A[m+1..q]))
void mergesort(int A[], int p, int q)
{
	if (!(p < q)) return;	//predicate: at least 2 elements to sort => stop when 1 element is left
	int m = (p + q)/2;
	mergesort(A, p, m);
	mergesort(A, m + 1, q);
	merge(A, p, m, q);
}//design: divide-conquer-combine
