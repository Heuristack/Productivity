 /**
 * TITLE:
 * AUTHOR: LiYing
 * DATE:
 * NOTE:
 */
#include<stdio.h>
#define MAXLINE 0x400

int main(int argc, char *argv[]){
	char name[L_tmpnam], line[MAXLINE];
	FILE *fp;

	printf("%s\n", tmpnam(NULL));

	tmpnam(name);
	printf("%s\n", name);

	if ((fp = tmpfile()) == NULL) {
		fprintf(stderr, "tmpfile failed\n");
		exit(-1);
	}/*tmpfile-failed*/
	fputs("one line of output", fp);
	rewind(fp);
	if (fgets(line, MAXLINE, fp) == NULL) {
		fprintf(stderr, "fgets failed\n");
		exit(-1);
	}/*fgets-failed*/

	fputs(line, stdout);
	exit(0);
}/*main*/
