/**
 * SUBJECT: Process Termination - 'exec' functions
 * AUTHOR: LiYing
 * TIME: 2009-10-22 14:31:22
 */

#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv[]){
	int i;
	char **ptr;
	extern char **environ;

	for (i = 0; i < argc; i++)
		printf("argv[%d]: %s\n", i, argv[i]);
	for (ptr = environ; *ptr != 0; ptr++)
		printf("%s\n", *ptr);
	exit(0);
}/*main*/
