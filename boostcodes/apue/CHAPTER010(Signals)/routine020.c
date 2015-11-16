/**
 * TITLE: sigsuspend function - Protecting a critical region from a signal
 * AUTHOR: LiYing
 * DATE: 2010-5-26 14:56:26
 * NOTE: blocking for waiting a signal delivery with a special signal mask
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
 * EXAMPLE1 -- protecting a critical region from a signal
 *
 */

#include<stdio.h>
#include<signal.h>
#include<errno.h>
#include<unistd.h>

void print_mask(const char *s);
static void sig_int(int);

int main(void){
	sigset_t newmask, oldmask, waitmask;
	struct sigaction sa;
	sa.sa_handler = sig_int;
	sigemptyset(&sa.sa_mask);
	print_mask("program start: ");
	if (sigaction(SIGINT, &sa, NULL) < 0){
		printf("main: call signal failed\n");
		exit(1);
	}/*signal*/

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);

	/*set signal mask to block SIGINT*/
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		printf("main: call sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/

	/**
	 * critical region
	 */
	print_mask("in critical region: ");

	/**
	 * Pause, allow all signals except SIGUSR1
	 */
	if (sigsuspend(&waitmask) != -1){
		printf("main: sigsuspend failed\n");
		exit(1);
	}/*sigsuspend*/
	print_mask("after return from sigsuspend: ");


	/*restore process signal mask that blocks SIGINT*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		printf("main: sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/

	print_mask("program exit: ");

	exit(0);
}/*main*/

static void
sig_int(int signo){
	print_mask("\nin sig_int: ");
}/*sig_int*/

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


/*AIX Dv_P59C1_M 3 5 00C3F6DF4C00
program start:
in critical region: SIGINT
^C
in sig_int: SIGUSR1
after return from sigsuspend: SIGINT
program exit:
*/
