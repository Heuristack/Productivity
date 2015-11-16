/**
 * TITLE: Calling read with a timeout
 * AUTHOR: LiYing
 * DATE: 2010-5-17 11:13:19
 * NOTE: 1.a race condition between the first call to alarm and the call to read;
 *		 2.If system calls are automatically restarted, the read is not interrupted when the SIGALRM signal handler returns.
 */

#include<setjmp.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

#define MAXLINE 1024

static void sig_alrm(int);

int main(int argc, char *argv[]){
	int n;
	char line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
		perror("signal install failed\n");
		exit(1);
	} /*if-signal-failed*/

	alarm(10);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
		perror("read error");
		exit(1);
	} /*if-read-failed*/
	alarm(0);

	write(STDOUT_FILENO, line, n);
	exit(0);
}/*main*/

static void sig_alrm(int signo){
	/*nothing to to, just return to interrupt the read*/
}/*sig_alrm*/
