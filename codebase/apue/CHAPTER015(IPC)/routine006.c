/**
 * TITLE: Filter to convert uppercase characters to lowercase
 * AUTHOR: LiYing
 * DATE: 2010-5-12 13:57:13
 * NOTE: 1.read from stdin; 2.process the input string; 3.write to stdout;
 */

#include<ctype.h>
#include<stdio.h>

int main(int argc, char *argv[]){
	int c;
	while((c = getchar()) != EOF){
		if (isupper(c))
			c = tolower(c);
		if (putchar(c) == EOF){
			printf("putchar failed\n");
			exit(1);
		}/*write*/
		if (c == '\n')
			fflush(stdout);
	}/*read&write: character-by-character*/
	exit(0);
}/*main*/
