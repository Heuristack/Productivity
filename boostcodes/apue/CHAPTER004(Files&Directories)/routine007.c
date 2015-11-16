/**
 * TITLE: Example of chdir function
 * AUTHOR: LiYing
 * DATE: 2010-6-10 11:19:47
 * NOTE:
 */
#include<stdio.h>
#include<unistd.h>

main(){
	int r;
	r = chdir("/tmp");
	if (r < 0) {
		fprintf(stderr, "chdir failed\n");
		exit(-1);
	}/*chdir-failed*/
	printf("chdir to /tmp\n");
	exit(0);
}/*main*/
