/**
 * TITLE: chmod function
 * AUTHOR: LiYing
 * DATE: 2010-6-7 10:52:16
 * NOTE:
 */
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	struct stat statbuf;
	int r;
	r = stat("foo", &statbuf);
	if (r < 0) {
		fprintf(stderr, "stat failed\n");
		exit(-1);
	}/*failed*/

	system("ls -l foo");
	/*turn on set-group-ID and turn off group-execute*/
	r = chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID);	/*set-group-id*/
	if (r < 0) {
		fprintf(stderr, "chmod failed\n");
		exit(-1);
	}/*failed*/

	system("ls -l foo");
	system("ls -l bar");
	/*set absolute mode to "rw-r--r--"*/
	r = chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (r < 0) {
		fprintf(stderr, "chmod failed\n");
		exit(-1);
	}/*failed*/

	system("ls -l bar");
	exit(0);
}/*main*/
