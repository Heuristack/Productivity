 /**
 * TITLE:
 * AUTHOR: LiYing
 * DATE:
 * NOTE:
 */

#include<stdio.h>
void pr_stdio(const char *name, FILE *fp);

int main(int argc, char *argv[]){
	FILE *fp;

	fputs("enter any character\n", stdout);
	if (getchar() == EOF) {
		fprintf(stderr, "getchar error\n");
	}/*eof*/
	fputs("one line to standard error\n", stderr);
	pr_stdio("stdin", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);

	if ((fp = fopen("/etc/motd", "r")) == NULL) {
		fprintf(stderr, "fopen failed\n");
		exit(-1);
	}/*fopen-failed*/
	if (getc(fp) == EOF) {
		fprintf(stderr, "getc-failed\n");
		exit(-1);
	}/*getc-failed*/

	pr_stdio("/etc/motd", fp);
	exit(0);
}/*main*/

void
pr_stdio(const char *name, FILE *fp){
	printf("stream:%s: ", name);
	if (fp->_flags && _IOFBF)
		printf("fully-buffered");
	if (fp->_flags && _IOLBF)
		printf("line-buffered");
	if (fp->_flags && _IONBF)
		printf("unbuffered");
	printf(", buffer size = %d\n", (fp->_bufendp - fp->_base));	//AIX
}/*pr_stdio*/
