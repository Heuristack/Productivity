/**
 * TITLE: POSIX.1 implementation of abort
 * AUTHOR: LiYing
 * DATE: 2010-5-26 11:32:32
 * NOTE:
 */
/**
 * FUNCTION PROTOTYPE
 * #include<stdlib.h>
 * 		void abort(void);
 * returns: never retures
 */
/**
 * IMPLEMENTATION -
 * Implementation of POSIX.1 abort
 * SIGABRT-branching
 *
 */

#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>

void myabort(void){
	sigset_t mask;
	struct sigaction action;

	/**
	 * Make sure SIGABRT 's disposition is not SIG_IGN
	 */
	sigaction(SIGABRT, NULL, &action);
	if (action.sa_handler == SIG_IGN) {
		action.sa_handler = SIG_DFL;
		sigaction(SIGABRT, &action, NULL);
	} /*SIG_IGN*/

	if (action.sa_handler == SIG_DFL)
		fflush(NULL);
	/**
	 * Make sure SIGABRT is not blocked
	 */
	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	/**
	 * Send SIGABRT to process itself
	 */
	kill(getpid(), SIGABRT);

	/**
	 * SIGABRT 's handler returns
	 */
	fflush(NULL);
	action.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &action, NULL);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);
	exit(1);	/*never executed*/
}/*abort*/

int main(int argc, char *argv[]){
	printf("main: beginning ... ");
	myabort();
	printf("main: ending ... "); 	/*never executed*/
}/*main*/
