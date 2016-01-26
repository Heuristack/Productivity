#include "sorting.h"

/**
 * Sort by Exchange (Transposition)
 * - systematically interchange elements out of order until no more such
 *
 *
**/

// bubblesort(sortbyselectionbyexchange): sorting A[n] by reducing 'inverse'-pairs exchaustively
void bubblesort(int A[], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j > i; j--) {
			if (A[j] < A[j-1])
				exchange(&A[j], &A[j-1]);
		}
	} //inviriant: A[0..i] in final position
}

// shellsort: diminishing incremental sorting by exchange (Knuth:TAOCP.v2.p84.D)
void shellsort(int A[], int n)
{
	int h = 1;
	while (h < n) h = 3*h + 1;
	while (h > 0) { //assertion: h(0) = 1
	    h = h / 3;
	    for (int k = 0; k < h; k++) {
	    	int i;
	    	int t = A[k];
	    	for (i = k; i + h < n && A[i+h] < t; i += h)
	    		A[i] = A[i+h];
	    	A[i] = t;
	    } //insertion sort a[k:h:n] (a[start:step:stop])
    } //invariant: each h-sub-array is sorted
}

// shellsortmcgs: Marcin Ciura's Gap Sequence
void shellsortmcgs(int A[], int n)
{
	int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1, 0};
	for (int g = 0, gap = gaps[0]; gap != 0; gap = gaps[g++]) {
		for (int i = gap; i < n; i++) {
			int j;
			int t = A[i];
			for (j = i; j >= gap && A[j - gap] > t; j -= gap) {
				A[j] = A[j - gap];
			}
			A[j] = t;
		}
	} //foreach (gap in gaps)
}
