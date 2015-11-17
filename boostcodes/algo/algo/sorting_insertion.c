#include "sorting.h"

/**
 * Sort by Insertion:
 * 	for each element e in unsorted set U
 *	  insert e into sorted set S
 *
 * insertsort: search position for each element then insert
 * insert -> searchposition on ordered set (assuming not existance)
 *
 * "insert" into ordered set => search position and insert
 * >> as opposite to "select"
 * "select" from unordered set => search element and delete
 *
 *
 * (order, record)
 * searchforinsert(record) returns order
 * searchforselect(order) returns record
 *
 *
 * Note:
 *  In case set is implemented on array
 *	- an index i is used to 'define' 2 sets
 *  - exchange (swap) is used for the sematic of 'delete & append'
 *
 * Pros of Insertion:
 *  - no need to know all elements beforehand
 *  - element can arrive in realtime
 *
 * Cons of Insertion:
 *  - insert on array-based set cause shifting
 *
**/

// searchposition: search the 'position' for record 'r' in sorted A[p..q]
int searchposition(int A[], int p, int q, int r)
{
	int position;
	for (position = p; position <= q; position++) {
		if (A[position] > r) break;
	} //invariant: A[p..position] <= r
	return position;
} //runtime: O(n)

// binarysearchposition: halve down the searching range [p..q] until 'qp' appears
int binarysearchposition(int A[], int p, int q, int r)
{
	while (p <= q) {
		int m = (p + q) / 2;
		if (r == A[m]) return m;
		if (r < A[m]) q = m - 1;
		if (r > A[m]) p = m + 1;
	}
	if ((p - q) == 1) return p;
}

// rightshift: shift A[p..q] to A[p+s, q+s]
void rightshift(int A[], int p, int q, int s)
{
	for (int i = q; i >= p; i--) {
		A[i+s] = A[i];
	} //invariant: A[i..q] are shifted to A[i+s..q+s]
} //runtime: O(n)

// insertbyshift: insert record 'r' into its final position
void insertbyshift(int A[], int p, int q, int r)
{
	int position = searchposition(A, p, q, r);
	rightshift(A, position, q, 1);
	A[position] = r;
} //runtime: O(n)

// insertbyexchange: insert record 'r' into its final position
void insertbyexchange(int A[], int p, int q, int r)
{
	A[q+1] = r;
	for (int i = q; i >= p; i--)
		if (A[i] > A[i+1]) exchange(&A[i], &A[i+1]);
} //runtime: O(n)

// insertsortbyshift: for each element e in unsorted set A[i..n-1]: insert e into the sorted set A[0..i-1]
void insertsortbyshift(int A[], int n)
{
	for (int i = 1; i < n; i++) {
		insertbyshift(A, 0, i-1, A[i]);
	} //invariant: A[0..i] are sorted
} //runtime: O(n**2)

void insertsortbyexchange(int A[], int n)
{
	for (int i = 1; i < n; i++) {
		insertbyexchange(A, 0, i-1, A[i]);
	} //invariant: A[0..i] are sorted
}

// sortbyinsertionbyshift: insertion by shifting - 'big' exchange
void sortbyinsertionbyshifting(int A[], int n)
{
	int i, j;
	for (j = 1; j < n; j++) {
		int t = A[j];
		for (i = j - 1; !(i < 0) && A[i] > t; i--) {
			A[i+1] = A[i];
		} //invariant: position for A[j] is found and made up
		A[i+1] = t;
	} //invariant: A[0..j] is sorted
}

// sortbyinsertionbyexchange: insertion by exchange - repreated exchange
void sortbyinsertionbyexchange(int A[], int n)
{
	for (int j = 1; j < n; j++) {
		for (int i = j - 1; !(i < 0) && A[i] > A[i+1]; i--) {
			exchange(&A[i], &A[i+1]);
		} //invariant: A[j] is inserted
	} //invariant: A[0..j] is sorted
}
