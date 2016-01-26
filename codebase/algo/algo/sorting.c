#include "sorting.h"

/**
 * Exchange / Transposition / Interchange
 * - 'exchange' generally swap values of a pair of variables
 * - 'interchange' swap positions of element in array based set
 * - 'interchange' directly reduce one 'inverse'
 *
**/

// exchange: exchange the value of a and b
void exchange(int *a, int *b)
{
	int t = *a; *a = *b; *b = t;
}

// indexedexchange: exchange the i-th and j-th element of array A
void interchange(int A[], int i, int j)
{
	int t = A[i]; A[i] = A[j]; A[j] = t;
}

