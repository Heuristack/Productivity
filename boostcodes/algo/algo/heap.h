#ifndef heap_h
#define heap_h

#include <limits.h>
/**
 * Binary Heap is [from CLRS3]
 * - an array data structure (object), A
 * - can be viewed as a nearly complete binary tree
 *
 * - elements in the array: A[1..length]
 * - valid elements in the heap: A[1..heap_size]
 * - 0 <= heap_size <= length
 *
**/

#define STORESIZE 0x400

typedef int num;

typedef struct heap {
	num store[STORESIZE+1];
	int length;
	int heap_size;
} heap_t;

int initheapstore(heap_t *H, int A[], int n);
void printheapstore(heap_t *H);
void printheap(heap_t *H, int i);
void build_max_heap(heap_t *H);
void sort_heap(heap_t *H);

#endif
