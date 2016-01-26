/**
 * TITLE: POSIX.1 implementation of sleep
 * AUTHOR: LiYing
 * DATE: 2010-5-26 11:33:19
 * NOTE:
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * unsigned int sleep(unsigned int seconds);
 * returns: zero or number of slept seconds
 */
/**
 * SLEEP -- CAUSE CALLING PROCESS TO BE SUSPENDED UNTIL EITHER
 * 1.The amount of wall clock time specified by seconds has elapsed;
 * 2.A signal is caught by the process and the signal handler returns;
 */
/**
 * NOTE:
 * the actual return may be at a time later than requested, because of other system activity
 */
/**
 * RETURNS:
 * 1.zero
 * 2.number of unslept seconds
 */
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

static void sig_alrm(int signo){
	/**
	 * nothing to do;
	 * just returning wakes up sigsuspend();
	 */
}/*sig_alrm*/

unsigned int mysleep(unsigned int nsecs){
	struct sigaction newact, oldact;
	sigset_t newmask, oldmask, suspmask;
	unsigned int unslept;

	/**
	 * programming paradigm -- using sigaction structure and function
	 * Step1: declare and initialize sigaction structure
	 * sa_handler
	 * sa_mask
	 * sa_flags
	 * sa_sigaction
	 * Step2: call sigaction function to install the signal handler
	 */
	/**
	 * install the signal handler
	 * SIGALRM -> sig_alrm: using sigaction
	 * restore old sigaction structure
	 */
	newact.sa_handler = sig_alrm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);

	/**
	 * programming paradigm -- using signal set operation
	 * Step1: declare signal set parameters
	 * Step2: empty the signal set to initialize the signet
	 * Step3: add the special signal into the signal set
	 * Step4: using the prepared signal set to sigprocmask
	 */
	/**
	 * block the signal SIGALRM
	 * SIGALRM blocked: using sigprocmask
	 * WHY BLOCK ALARM?
	 */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);

	/*set the timer*/
	alarm(nsecs);

	/*wait the timer expires*/
	suspmask = oldmask;
	sigdelset(&suspmask, SIGALRM);
	sigsuspend(&suspmask);

	/*return from blocking with the system call sigsuspend interrupted*/
	unslept = alarm(0);

	/*reset signal disposition for SIGALRM*/
	sigaction(SIGALRM, &oldact, NULL);
	/*reset signal mask which blocks SIGALRM */
	sigprocmask(SIG_SETMASK, &oldmask, NULL);

	return (unslept);
}/*sleep*/

main(){
	printf("main: begin sleep ... \n");
	mysleep(3);
	printf("main: wakes up !!! \n");
}/*main*/
