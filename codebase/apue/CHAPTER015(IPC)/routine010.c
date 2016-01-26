/**
 * TITLE: Filter to add two numbers, using standard I/O
 * AUTHOR: LiYing
 * DATE: 2010-5-13 9:39:49
 * NOTE: 1.standard I/O functions;2.paradigm of reading&writing loop
 */

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define MAXLINE 1024

int main(int argc, char *argv[]){
	int int1, int2;
	char line[MAXLINE];

	while (fgets(line, MAXLINE, stdin) != NULL) {
		if (sscanf(line, "%d%d", &int1, &int2) == 2) {
			if (printf("%d\n", int1 + int2) == EOF) {
				printf("printf error\n");
				exit(1);
			}/*printf error*/
		}/*read&write*/
		else if (printf("invalid args\n") == EOF) {
			printf("printf error\n");
			exit(1);
		}/*invalid args*/
	}/*read&write-loop*/
	exit(0);
}/*main*/
