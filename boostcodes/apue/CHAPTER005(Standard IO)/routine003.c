/**
 * TITLE: Opening and Closing a Stream
 * AUTHOR: LiYing
 * DATE: 2010-6-12 9:33:36
 * NOTE:
 */
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
	FILE *fp;
	int fd;

	fp = fopen("./hello.c", "w+");
	if (fp == NULL)
		printf("fopen failed\n");

	fprintf(fp, "hello\n");

	fp = freopen("./hello.c", "w+", fp);
	fprintf(fp, "helloworld\n");

	fd = open("./hello.c", O_RDWR);
	fp = fdopen(fd, "w+");
	fprintf(fp, "helloworld111\n");

	exit(0);
}/*main*/
