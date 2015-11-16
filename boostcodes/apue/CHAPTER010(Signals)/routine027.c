/**
 * TITLE: Calling read with a timeout, using longjmp
 * AUTHOR: LiYing
 * DATE: 2010-5-17 11:07:38
 * NOTE: interactions with other signal handlers
 */
#include<setjmp.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

#define MAXLINE 1024

static jmp_buf env_alrm;
static void sig_alrm(int);


int main(int argc, char *argv[]){
	int n;
	char line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
		perror("signal install failed\n");
		exit(1);
	} /*if-*/
	if (setjmp(env_alrm) != 0) {
		perror("read timeout");
		exit(1);
	} /*if-*/
	alarm(10);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
		perror("read error");
		exit(1);
	} /*if-*/
	alarm(0);

	write(STDOUT_FILENO, line, n);
	exit(0);
}/*main*/

static void sig_alrm(int signo){
	longjmp(env_alrm, 1);
}/*sig_alrm*/
