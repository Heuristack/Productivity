 /**
 * TITLE: Print file flags for specified descriptor
 * AUTHOR: LiYing
 * DATE: 2010-6-13 9:38:59
 * NOTE:
 */

#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int fs;

	if (argc != 2) {
		fprintf(stderr, "usage: exec <descriptor#>\n");
		exit(-1);
	} /*illegal argument*/

	fs = fcntl(atoi(argv[1]), F_GETFL, 0);
	if (fs < 0) {
		fprintf(stderr, "main: fcntl failed\n");
		exit(-1);
	}/*fcntl-failed*/

	switch (fs & O_ACCMODE) {
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read and write");
			break;
		default:
			printf("unknow access mode");
			exit(0);
	} /*access permission*/

	if (fs & O_APPEND)
		printf("; append");
	if (fs & O_NONBLOCK)
		printf("; nonblocking");
#if defined (O_SYNC)
	if (fs & O_SYNC)
		printf("; synchronous writes");
#endif
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
	if (fs & O_FSYNC)
		printf("; synchronous writes");
#endif
	printf("\n");
	exit(0);
}/*main*/

/*---------------------------------------
$ exec001 1
read and write
$ exec001 0 < /dev/tty
read only
$ exec001 1 > temp.foo
$ cat temp.foo
write only
$ exec001 2 2>>temp.foo
write only; append
$ exec001 5 5<>temp.foo
read and write
---------------------------------------*/
