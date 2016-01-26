/**
 * TITLE: access function
 * AUTHOR: LiYing
 * DATE: 2010-6-7 9:06:22
 * NOTE:
 */
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
	int result;

	if (argc != 2){
		fprintf(stderr, "illegal argument\n");
		exit(-1);
	}/*illegal argument*/

	result = access(argv[1], R_OK);
	if (result < 0)
		fprintf(stderr, "access failed\n");
	else
		fprintf(stderr, "read access OK\n");
	result = open(argv[1], O_RDONLY);
	if (result < 0)
		fprintf(stderr, "open failed\n");
	else
		fprintf(stderr, "open for reading OK\n");
	exit(0);
}/*main*/
