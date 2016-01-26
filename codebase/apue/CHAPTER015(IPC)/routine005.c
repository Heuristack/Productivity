/**
 * TITLE: Copy file to pager program using popen
 * AUTHOR: LiYing
 * DATE: 2010-5-12 10:35:32
 * NOTE: creating a pipe, forking a child, closing the unused ends of the pipe, executing a shell to run the command, and waiting for the command to terminate
 */
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define PAGER   "${PAGER:-more}" /* environment variable, or default */
#define MAXLINE 1024

int main(int argc, char *argv[]){
	char line[MAXLINE];
	FILE *fpin, *fpout;

	if (argc != 2) {
		printf("usage: %s <pathname>\n", argv[0]);
		exit(1);
	}/*argument illegal*/
	if ((fpin = fopen(argv[1], "r")) == NULL) {
		printf("cant't open %s\n", argv[1]);
		exit(1);
	}/*fopen*/

	if ((fpout = popen(PAGER, "w")) == NULL){
		printf("popen failed\n");
		exit(1);
	}/*popen*/

	while(fgets(line, MAXLINE, fpin) != NULL){
		if (fputs(line, fpout) == EOF){
			printf("fputs to pipe error\n");
			exit(1);
		}/*fputs error*/
	}/*read&write: line-by-line*/

	if (ferror(fpin)){
		printf("fgets error\n");
		exit(1);
	}/*ferror*/
	if (pclose(fpout) == -1){
		printf("pclose error\n");
		exit(1);
	}/*pclose*/
	exit(0);
}/*main*/
