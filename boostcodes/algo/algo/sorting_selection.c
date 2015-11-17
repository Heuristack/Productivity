#include "sorting.h"

/**
 * Sort By Selection:
 * 	select and delete the minimum element e from unsorted set U
 *  append e to sorted set S
 *  until U is empty
 *
 * selectsort: search element for each position
 * select -> searchelement on ordered (nonordered) set (asuming existance)
 *
 * Note:
 *  In case set is implemented on array
 *	- an index i is used to 'define' 2 sets: A[p..i] and A[i+1..q]
 *  - exchange (swap) is used for the sematic of 'delete & append'
 *
 * "select" from unordered set => search element and delete
 * >> as opposite to "insert"
 * "insert" into ordered set => search position and insert
 *
 * (order, record)
 * searchforinsert(record) returns order
 * searchforselect(order) returns record
 *
 * Selection Problem
 *  - Input: A[1..n] of n distinguished numbers and i in [1..n]
 *  - Output: the element larger than exactly (i-1) other elements of A
 *
 * Cons of Selection:
 *  - Precondition: All input element should be present beforehand
 *
 * Pros of Selection:
 *  - Final position can be found (no shifting like insertion)
 *
**/

// searchelement: thoroughly search record r in A[p..q] (if not found return q+1)
int searchelement(int A[], int p, int q, int r)
{
	int i;
	for (i = p; i <= q; i++) {
		if (A[i] == r) break;
	} //invariant: r not in A[p..i]
	return i;
} //runtime: O(n)

// minelement: return order(+1) element of A[p..q]
int minelement(int A[], int p, int q)
{
	int minimum = A[p];
	for (int i = p; i <= q; i++) {
		if (A[i] < minimum) minimum = A[i];
	} //invariant: minimum is order(+1) in A[p..i]
	return minimum;
}

// maxelement: return order(-1) of A[p..q]
int maxelement(int A[], int p, int q)
{
	int maximum = A[p];
	for (int i = p; i <= q; i++) {
		if (A[i] > maximum) maximum = A[i];
	} //invariant: maximum is order(-1) in A[p..i]
	return maximum;
}

// select: return position of order-th element
int select(int A[], int p, int q, int order)
{
	if (order != 1) return -1; // current only order(1)
	int order1 = minelement(A, p, q);
	return searchelement(A, p, q, order1);
}

// selectsort: select and delete minimum element until empty
void selectsort(int A[], int n)
{
	for (int i = 0; i < n; i++) {
		int m = select(A, i, n-1, 1);
		exchange(&A[i], &A[m]);
	} //invariant: A[0..i] in final position
} //runtime: O(n**2)


// selectmin: find and return the index of the minimum element
int selectmin(int A[], int p, int q)
{
	int m = p;
	for (int i = p; i <= q; i++) {
		if (A[i] < A[m]) m = i;
	} //invariant: A[m] <= A[p..i]
	return m;
} //runtime: O(n)

// selectminsort: select and delete minimum element until empty
void selectminsort(int A[], int n)
{
	for (int i = 0; i < n; i++) {
		int m = selectmin(A, i, n-1);
		exchange(&A[i], &A[m]);
	} //invariant: A[0..i] in final position
} //runtime: O(n**2)

// reselectsort: recursively select minimum element
void reselectminsort(int A[], int p, int q)
{
	if (p == q) return;
	int m = selectmin(A, p, q);
	exchange(&A[p], &A[m]);
	reselectminsort(A, p + 1, q);
}

// selectionsort: select and delete minimum element until empty
void selectionsort(int A[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		int m = i;
		for (int j = i + 1; j < n; j++) {
			if (A[j] < A[m]) m = j;
		} //invariant: A[m] smallest of A[i..n]
		exchange(&A[i], &A[m]);
	} //invariant: A[0..i] in final position
}

// reselectsort: recursively select minimum element
void reselectionsort(int A[], int i, int n)
{
	int j, m;
	if (i == n - 1) return;
	for (m = i, j = i + 1; j < n; j++)
		if (A[j] < A[m]) m = j;
	exchange(&A[m], &A[i]);
	reselectionsort(A, i + 1, n);
}

// siftup: name of this operation comes from [Knuth.TAOCP2.p145]
void siftup(int H[], int n, int i)
{
	if (!(i < n)) return;

	int m = i;
	int p = 2 * i + 1;
	int q = 2 * i + 2;

	if (p < n && H[i] < H[p]) m = p;
	if (q < n && H[i] < H[q]) m = q;

	if (m != i) {
		exchange(&H[m], &H[i]);
		siftup(H, n, m);
	}
}

// sortbysiftup: heapsort
void sortbysiftup(int A[], int n)
{
	for (int i = n - 1; i >= 0; i--) {
		siftup(A, n, i);
	}
	for (int i = n - 1; i >= 0; i--) {
		exchange(&A[0], &A[i]);
		siftup(A, i, 0);
	}
}



