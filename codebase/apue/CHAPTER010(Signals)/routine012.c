/**
 * TITLE: Blocking Signals Using Sigprocmask
 * AUTHOR: LiYing
 * DATE: 2010-5-17 15:31:01
 * NOTE: getting old signal mask using sigprocmask(0, NULL, &oset)
 * 		 signal mask of a process is the set of signals currently blocked from delivery to that process
 */
/**
 * FUNCTION PROTOTYPE -- examine and change blocked signals
 * #include<signal.h>
 * int sigprocmask(int how,
 * 				   const sigset_t *restrict set,
 * 				   sigset_t *restrict oset);
 * returns: zero if OK, minus one on error
 */
/**
 * SIGPROCMASK ARGUMENTS -- HOW
 * SIG_BLOCK
 * SIG_UNBLOCK
 * SIG_SETMASK
 * 0
 */

#include<signal.h>
#include<errno.h>
#include<stdio.h>
#include<unistd.h>

void print_mask(const char *s);

main(){
	sigset_t s, os;

	sigemptyset(&s);
	sigaddset(&s, SIGBUS);

	sigprocmask(SIG_BLOCK, &s, &os);

	print_mask("hello: ");
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
