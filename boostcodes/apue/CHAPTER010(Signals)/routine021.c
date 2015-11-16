/**
 * TITLE: sigsuspend function - Using sigsuspend to wait for a global variable to be set
 * AUTHOR: LiYing
 * DATE: 2010-5-26 15:54:03
 * NOTE:
 */
/**
 * FUNCTION PROTOTYPE -- sigsuspend
 * #include<signal.h>
 * int sigsuspend(const sigset_t *sigmask);
 * returns: minus one with errno set to EINTR
 */
/**
 * REMARKS
 * The signal mask of the process is set to the value pointed to by sigmask.
 * Then the process is suspended until a signal is caught or until a signal occurs that terminates the process.
 * If a signal is caught and if the signal handler returns, then sigsuspend returns, and
 * the signal mask of the process is set to its value before the call to sigsuspend.
 */
/**
 * EXAMPLE2 -- using sigsuspend to wait for a global variable to be set
 *
 */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<errno.h>

volatile sig_atomic_t quitflag;
void print_mask(const char *s);

static void
sig_int(int signo){
	if (signo == SIGINT)
		printf("\ninterrupt");
	else if (signo == SIGQUIT)
		quitflag = 1;
	print_mask("\nsin_int:mask: ");
}/*sig_int*/


int main(){
	struct sigaction sa, osa;
	sa.sa_handler = sig_int;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigset_t newmask, oldmask, zeromask;

	if (sigaction(SIGINT, &sa, NULL) < 0){
		printf("main: signal(SIGINT) failed\n");
		exit(1);
	}/*signal desposition1*/
	if (sigaction(SIGQUIT, &sa, NULL) < 0){
		printf("main: signal(SIGQUIT) failed\n");
		exit(1);
	}/*signal desposition2*/

	print_mask("main:before sigprocmask:mask: ");
	/**
	 * Block SIGQUIT, save signal mask
	 */
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		printf("main: 1st call sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/

	print_mask("main:before sigsuspend:mask: ");
	while (quitflag == 0)
		sigsuspend(&zeromask);

	quitflag = 0;

	print_mask("main:after sigsuspend:mask: ");
	/**
	 * restore signal mask that blocks SIGQUIT
	 */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		printf("main: 2nd call sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/
	print_mask("main:after restore:mask: ");

	exit(0);
}/*main*/


void print_mask(const char *s){
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if (sigprocmask(0, NULL, &sigset) < 0){
		printf("print_maks: call sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/
	printf("%s", s);
	if (sigismember(&sigset, SIGABRT))	printf("SIGABRT ");
	if (sigismember(&sigset, SIGALRM))	printf("SIGALRM ");
	if (sigismember(&sigset, SIGBUS	))	printf("SIGBUS	");
	if (sigismember(&sigset, SIGCHLD))	printf("SIGCHLD ");
	if (sigismember(&sigset, SIGCONT))	printf("SIGCONT ");
	if (sigismember(&sigset, SIGFPE	))	printf("SIGFPE	");
	if (sigismember(&sigset, SIGHUP	))	printf("SIGHUP	");
	if (sigismember(&sigset, SIGILL	))	printf("SIGILL	");
	if (sigismember(&sigset, SIGINT	))	printf("SIGINT	");
	if (sigismember(&sigset, SIGKILL))	printf("SIGKILL ");
	if (sigismember(&sigset, SIGPIPE))	printf("SIGPIPE ");
	if (sigismember(&sigset, SIGQUIT))	printf("SIGQUIT ");
	if (sigismember(&sigset, SIGSEGV))	printf("SIGSEGV ");
	if (sigismember(&sigset, SIGSTOP))	printf("SIGSTOP ");
	if (sigismember(&sigset, SIGTERM))	printf("SIGTERM ");
	if (sigismember(&sigset, SIGTSTP))	printf("SIGTSTP ");
	if (sigismember(&sigset, SIGTTIN))	printf("SIGTTIN ");
	if (sigismember(&sigset, SIGTTOU))	printf("SIGTTOU ");
	if (sigismember(&sigset, SIGURG	))	printf("SIGURG	");
	if (sigismember(&sigset, SIGUSR1))	printf("SIGUSR1 ");
	if (sigismember(&sigset, SIGUSR2))	printf("SIGUSR2 ");
	printf("\n");
	errno = errno_save;
}/*print_maks*/
