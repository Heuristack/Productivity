/**
 * SUBJECT: job-control signals
 * AUTHOR: LiYing
 */
/**
 * SIX JOB-CONTROL SIGNALS
 * SIGCHLD -- child process has stopped or terminated
 * SIGCONT -- continue process, if stopped
 * SIGSTOP -- stop signal (can't be caught or ignored)
 * SIGTSTP -- interactive stop signal
 * SIGTTIN -- read from controlling terminal by member of a background process group
 * SIGTTOU -- write to controlling terminal by member of a background process group
 */
/**
 * Interaction between job-control signals
 * When STOP signals arrivals, pending CONT signal is discarded;
 * When CONT signal arrivals, pending STOP signal is discarded;
 */
/**
 * JOB CONTROL TASKS:
 * T-STOP: SIGSTOP | SIGTSTP | SIGTTIN | SIGTTOU
 * C-CONT: SIGCONT
 */
/**
 * SIGNAL HANDLERS LIFETIME
 *
 */
/**
 * What is the meaning of JOB control?
 * What is the relationship between shell and applications?
 * What is job-control shell?
 * How to input the job-control signals in shell?
 * Why process managing terminal is special for example vi editor?
 */
/**
 * SIGTSTP: suspend character Ctr-Z
 * SIGTTIN:
 * SIGTTOU:
 * SIGSTOP:
 */
/**
 * INHERITENCE
 * Signal Disposition could be inherited by child process
 */
/**
 * EXAMPLE -- How to handle signal SIGTSTP`
 */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

#define BUFFSIZE 1024

static void handler(int signo){
	printf("handler: catch signal SIGUSR1\n");
	signal(SIGUSR1, handler);
}/*handler*/

static void sig_tstp(int signo);

int main(){
	int n;
	char buf[BUFFSIZE];

	if (signal(SIGTSTP, SIG_IGN) == SIG_DFL)
		signal(SIGTSTP, sig_tstp);

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n){
        	printf("main: write error\n");
        	exit(1);
        }/*write*/
	exit(0);
}/*main*/

static void
sig_tstp(int signo){/*signal handler for SIGTSTP*/
	sigset_t mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGTSTP);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	signal(SIGTSTP, SIG_DFL);
	kill(getpid(), SIGTSTP);
	signal(SIGTSTP, sig_tstp);
}/*sig_tstp*/
