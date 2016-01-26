/**
 * TITLE: Invoke uppercase/lowercase filter to read commands
 * AUTHOR: LiYing
 * DATE: 2010-5-12 14:10:33
 * NOTE: read-write loop manners: line-by-line/character-by-character/
 */
#include<stdio.h>
#include<sys/wait.h>
#define MAXLINE 1024
#define FILTER "./executable006"

int main(int argc, char *argv[]){
	char line[MAXLINE];
	FILE *fpin;

	if ((fpin = popen(FILTER, "r")) == NULL){
		printf("popen failed\n");
		exit(1);
	}/*popen the filter*/

	for ( ; ; ) {
		fputs("promp> ", stdout);
		fflush(stdout);
		if (fgets(line, MAXLINE, fpin) == NULL) {
			break;
		}/*fgets*/
		if (fputs(line, stdout) == EOF) {
			printf("fputs failed\n");
			exit(1);
		}/*fputs*/
	}/*read&write loop: line-by-line*/

	if (pclose(fpin) == -1){
		printf("pclose failed\n");
		exit(1);
	}/*pclose the filter*/
	putchar('\n');
	exit(0);
}/*main*/
