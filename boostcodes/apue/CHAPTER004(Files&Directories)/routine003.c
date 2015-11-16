/**
 * TITLE: umask function
 * AUTHOR: LiYing
 * DATE: 2010-6-7 10:10:40
 * NOTE:
 */
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(int argc, char *argv[]){
	int r;
	umask(0);
	r = creat("foo", RWRWRW);
	if (r < 0) {
		fprintf(stderr, "create failed\n");
		exit(-1);
	}/*failed*/
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	r = creat("bar", RWRWRW);
	if (r < 0) {
		fprintf(stderr, "creat failed\n");
		exit(-1);
	}/*failed*/
	exit(0);
}/*main*/
