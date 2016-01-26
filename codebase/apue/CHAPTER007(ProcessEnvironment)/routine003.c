/**
 * Subject: Argument-List
 * Author: LiYing
 */

/**
 * Argument-Vector:
 * Array of pointer to array of characters
 * Pointer to array of pointer to array of chars
 */
/**
 * Argument-Counter:
 * 0, 1, ..., argc - 1
 * Number of arguments
 */
/**
 * Argument-Processing Loop
 * for (i = 0; i < argc; i++)
 * for (i = 0; argv[i] != NULL; i++)	(OK on HP-UX)
 */

#include<stdio.h>

int main(int argc, char *argv[]){
	int i;

	for (i = 0; i < argc; i++)
		printf("argv[%d] == \"%s\"\n", i, argv[i]);
	for (i = 0; argv[i] != NULL; i++)
		printf("argv[%d] == \"%s\"\n", i, argv[i]);
	exit(0);
}/*main*/
