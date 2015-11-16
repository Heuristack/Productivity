/**
 * TITLE: Simple filter to add two numbers
 * AUTHOR: LiYing
 * DATE: 2010-5-12 15:14:58
 * NOTE: filter is a program that reads from standard input and writes to standard output
 */
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define MAXLINE 1024

int main(int argc, char *argv[]){
	int n, int1, int2;
	char line[MAXLINE];

	while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0) {
		line[n] = 0;
		if (sscanf(line, "%d%d", &int1, &int2) == 2){
			sprintf(line, "%d\n", int1+int2);
			n = strlen(line);
			if (write(STDIN_FILENO, line, n) != n){
				printf("write to stdin error\n");
				exit(1);
			}/*write*/
		}/*read-write per line*/
		else if (write(STDOUT_FILENO, "invalid args\n", n) != 13){
			printf("write error\n");
			exit(1);
		}/*report error*/
	}/*read-write loop: line-by-line*/
	exit(0);
}/*main*/
