/**
 * Subject: Memory-Allocation
 * Author: LiYing
 */

/**
 * MEMORY-ALLOCATION FUNCTIONS (From the Heap)
 * malloc: 1.Allocates 'size' of bytes memory;
 *         2.The initial value of the memory is indeterminate.
 * calloc: 1.Allocates 'nobj * size' of bytes memory;
 *         2.The space is initialized to all 0 bits.
 * realloc:1.Increases or decreases the size of a previously allocated area;
 *         2.Return the pointer to the new memory segment;
 *         3.When the size increases, the initial value of the space between
 *           the old contents and the end of the new area is indeterminate.
 */
/**
 * FUNCTION PROTOTYPES
 * #include<stdlib.h>
 * 		void *malloc(size_t size);
 * 		void *calloc(size_t nobj, size_t size);
 * 		void *realloc(void *ptr, size_t newsize);
 * Return: Non-NULL pointer if OK, NULL on error
 * 		void *free(void *ptr);
 */
/**
 * ALIGNMENT
 * a suitable alignment is made.
 */
/**
 * POINTER TYPE CAST
 * Explict Cast
 * Implict Cast
 */
/**
 * DEALLOCATION
 * a malloc pool
 */
/**
 * REALLOCATE
 * Decrease: No attention!
 * Increase(move or not):The area may move, we shouldn't have any pointers into this area.
 */
/**
 * IMPLIMENTATION
 * sbrk: expands or contracts the heap of the process.
 */
/**
 * RECORD-KEEPING INFORMATION
 * Before the start of the allocated area.
 */
/**
 * CORRUPTION
 * Write before or behind the allocated area.
 */
/**
 * FREE USAGE
 * Free more times -> fatal error
 * Free pointer not obtained from 'malloc's -> fatal error
 * Not free -> memory leakage
 */
/**
 * VERSIONS WITH ADDITIONAL ERROR CHECKING
 * implimentation depended.
 */
/**
 * ALLOCA FUNCTION (From the Stack)
 * alloca: allocate space from the stack of the caller.
 */
/**
 * ALTERNATE MEMORY ALLOCATORS
 * libmalloc; vmalloc; quick-fit
 * HP-UX: mallopt; mallinfo; memorymap;
 */
#include<stdio.h>
#include<stdlib.h>
#include<alloca.h>

int main(int argc, char *argv[]){
	char *p = (char *)alloca(20*sizeof(char));
	strcpy(p, "hello world");
	printf("%s\n", p);
	exit(0);
}/*main*/
