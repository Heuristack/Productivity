/**
 * TITLE: Examining Pending Signals
 * AUTHOR: LiYing
 * DATE: 2010-5-17 15:45:25
 * NOTE: sigprocmask(SIG_BLOCK,...) && sigprocmask(SIG_UNBLOCK,...)
 *       After calling sigprocmask, if any unblocked signals are pending, at least one of these signals is delivered to the process
 *       BEFORE sigprocmask returns.
 */
/**
 * FUNCTION PROTOTYPE -- examine pending signals
 * #include<signal.h>
 * int sigpending(sigset_t *set);
 * returns: zero if OK, minus one on error
 */
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<errno.h>

static void sig_quit(int signo){
	printf("SIGQUIT HANDLER: Caught SIGQUIT\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR){
		printf("sig_quit: reset SIGQUIT error\n");
		exit(1);
	}/*reset the signal handler*/
}/*sig_quit*/

main(){
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR){
		printf("main: install sig_quit handler failed\n");
		exit(1);
	}/*install the signal handler for SIGQUIT*/

	/**
	 * Block SIGQUIT and save the current signal mask
	 */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask)){
		printf("main: calling sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/

	sleep(5);

	if (sigpending(&pendmask) < 0){
		printf("main: calling sigpending failed\n");
		exit(1);
	}/*sigpending*/
	if (sigismember(&pendmask, SIGQUIT)){
		printf("\nSIGQUIT pending\n");
	}/*sigismember*/

	/**
	 * Unblock SIGQUIT and reset the signal mask
	 */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL)){
		printf("main: calling sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/
	printf("SIGQUIT unblocked\n");

	sleep(5);

	exit(0);
}/*main*/
