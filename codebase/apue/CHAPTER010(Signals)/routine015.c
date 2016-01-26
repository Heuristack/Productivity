/**
 * TITLE: sigsetjmp && siglongjmp -- nonlocal branching
 * AUTHOR: LiYing
 * DATE: 2010-5-25 8:48:41
 * NOTE: sigsetjmp && siglongjmp should always be used when branching from a signal handler
 */

/**
 * RETURN FROM SIGNAL HANDLER vs RETURN TO THE MAIN LOOP OF A PROGRAM
 *
 */
#include<signal.h>
#include<setjmp.h>
#include<time.h>
#include<errno.h>

static void 					sig_usr1(int), sig_alrm(int);
static sigjmp_buf				jmpbuf;
static volatile sig_atomic_t	canjmp;
static void 					print_mask(const char *s);

int main(int argc, char *argv[]){
	struct sigaction sa1;
	struct sigaction sa2;

	sa1.sa_handler = sig_usr1;
	sigaction(SIGUSR1, &sa1, NULL);

	sa2.sa_handler = sig_alrm;
	sigaction(SIGALRM, &sa2, NULL);

	print_mask("main starting: ");

	if (sigsetjmp(jmpbuf, 1)) {
		print_mask("main ending: ");
		exit(1);
	}/*sigsetjmp*/
	canjmp = 1;
	while(1)
		pause();
}/*main*/

static void sig_usr1(int signo){
	time_t start_time;

	if (canjmp == 0)
		return;
	print_mask("sig_usr1: starting sig_usr1: ");
	alarm(3);
	start_time = time(NULL);
	for ( ; ; )							/*busy wait for 5 seconds*/
		if (time(NULL) > start_time + 5)
			break;
	print_mask("sig_usr1: finishing sig_usr1: ");

	canjmp = 0;
	siglongjmp(jmpbuf, 1);
}/*sig_usr1*/

static void sig_alrm(int signo){
	print_mask("sig_alrm: ");
}/*sig_alrm*/

static void print_mask(const char *s){
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
	if (sigismember(&sigset, SIGBUS	))	printf("SIGBUS ");
	if (sigismember(&sigset, SIGCHLD))	printf("SIGCHLD ");
	if (sigismember(&sigset, SIGCONT))	printf("SIGCONT ");
	if (sigismember(&sigset, SIGFPE	))	printf("SIGFPE ");
	if (sigismember(&sigset, SIGHUP	))	printf("SIGHUP ");
	if (sigismember(&sigset, SIGILL	))	printf("SIGILL ");
	if (sigismember(&sigset, SIGINT	))	printf("SIGINT ");
	if (sigismember(&sigset, SIGKILL))	printf("SIGKILL ");
	if (sigismember(&sigset, SIGPIPE))	printf("SIGPIPE ");
	if (sigismember(&sigset, SIGQUIT))	printf("SIGQUIT ");
	if (sigismember(&sigset, SIGSEGV))	printf("SIGSEGV ");
	if (sigismember(&sigset, SIGSTOP))	printf("SIGSTOP ");
	if (sigismember(&sigset, SIGTERM))	printf("SIGTERM ");
	if (sigismember(&sigset, SIGTSTP))	printf("SIGTSTP ");
	if (sigismember(&sigset, SIGTTIN))	printf("SIGTTIN ");
	if (sigismember(&sigset, SIGTTOU))	printf("SIGTTOU ");
	if (sigismember(&sigset, SIGURG	))	printf("SIGURG ");
	if (sigismember(&sigset, SIGUSR1))	printf("SIGUSR1 ");
	if (sigismember(&sigset, SIGUSR2))	printf("SIGUSR2 ");
	printf("\n");
	errno = errno_save;
}/*print_maks*/

/*sig_usr1: starting sig_usr1: SIGABRT SIGBUS SIGQUIT SIGSEGV SIGUSR1
sig_alrm: SIGABRT SIGALRM SIGBUS SIGQUIT SIGSEGV SIGUSR1
sig_usr1: finishing sig_usr1: SIGABRT SIGBUS SIGQUIT SIGSEGV SIGUSR1
main ending:
*/
