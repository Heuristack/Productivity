#include "sorting.h"

/**
 * Partition by Exchange
 * - given a set S[p..q]
 * - use index 'i' as a stick seperating 2 sets S[p..i-1] and S[i..q]
 * - check each element S[j] in S[i..q] (i <= j <= q)
 * - if a designed predict P(S[j]) is true, exchange S[i] and S[j] and increase i
 *
 * Result: for all 'j' in [p..q] such that P[S[j]] is true => S[j] in S[p..i-1]
 *
 * Note:
 * If P is comparasion to a given element S[pivot] (p <= pivot <= q),
 * then order number (position) of S[pivot] in S[p..q] is also found!!!
 *
 * Stick is defined by the index number on its left -- stickleft
 * [...s]|[s+1...] => [...s+1]|[s+2...]
 *
**/

// partitionpredicate: criterion of how to partition an array based set
int partitionpredicate(int base, int choose)
{
	return choose < base;
}

// partitionbyexchange: exchange based partition technique
int partitionbyexchange(int A[], int p, int q)
{
	int stickleft = p - 1;
	for (int i = p; i < q; i++) { // for each A[i] in A[p..q-1]
		if (partitionpredicate(A[q], A[i])) { // A[q] is base
			exchange(&A[++stickleft], &A[i]);
		} // predicate: A[stickright] !< A[q]
	} // inviriant: A[p..stickleft] < A[q] <= A[stickright..q]

	int stickright = stickleft + 1;
	exchange(&A[stickright], &A[q]);
	return stickright;
} //runtime: O(n)


// sortbypartitionbyexchange: divide and reduce unsorted set by 'partition'
void sortbypartitionbyexchange(int A[], int p, int q)
{
	if (!(p < q)) return;
	int m = partitionbyexchange(A, p, q);
	sortbypartitionbyexchange(A, p, m - 1);
	sortbypartitionbyexchange(A, m + 1, q);
}

// median3: return the median number among the three
int median3(int A[], int p, int m, int q)
{
	return m;
}

// partition3byexchange: [p..sp](sp..qs)[qs..q] (Entropy-optimal: Dutch National Flag problem)
void partition3byexchange(int A[], int p, int q, int *sp, int *qs)
{
	int m = (p + q)/2; m = median3(A,p,m,q); // Median-of-three
	int u, v = A[m];
	*sp = p - 1;
	*qs = q + 1;
	for (int i = p; u = A[i], i < *qs; i += (u <= v)) {
		if (u < v) exchange(&A[i], &A[++(*sp)]);
		if (u > v) exchange(&A[i], &A[--(*qs)]);
	}
}

// sortbyparition3byexchange:
void sortbypartition3byexchange(int A[], int p, int q)
{
	if (!(p < q)) return;
	int sp = 0;
	int qs = 0;
	partition3byexchange(A, p, q, &sp, &qs);
	sortbypartition3byexchange(A, p, sp);
	sortbypartition3byexchange(A, qs, q);
}


// partition: randomly choose a pivot then put pivot at A[q]
int randompartition(int A[], int p, int q)
{
	// int pivot = rand() % (q - p + 1) - 1;
	// exchange(&A[pivot], &A[q]);

	int stickleft = p - 1;
	for (int i = p; i < q; i++) {
		if (A[i] < A[q]) {
			exchange(&A[++stickleft], &A[i]);
		} // predicate: A[stickright] !< A[q]
	} // inviriant: A[p..stickleft] < A[q] <= A[stickright..q]

	int stickright = stickleft + 1;
	exchange(&A[stickright], &A[q]);
	return stickright;
}

// quicksort: partition-exchange sort
void quicksort(int A[], int p, int q)
{
	if (!(p < q)) return;
	int m = randompartition(A, p, q);
	quicksort(A, p, m - 1);
	quicksort(A, m + 1, q);
}


