/**
 * TITLE: Signal Set Mainpulation
 * AUTHOR: LiYing
 * DATE: 2010-5-17 15:29:22
 * NOTE: signal set initialization through sigemptyset or sigfillset (must be done before using the signal set)
 */
/**
 * FUNCTION PROTOTYPE -- SIGNAL SET OPERATIONS
 * #include<signal.h>
 * int sigemptyset(sigset_t *set);
 * int sigfillset(sigset_t *set);
 * int sigaddset(sigset_t *set, int signo);
 * int sigdelset(sigset_t *set, int signo);
 * returens: zero if OK, minus one on error
 *
 * int sigismember(const sigset_t *set, int signo);
 * returns: one if ture, zero if false, minus one on error
 */
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

main(){
	sigset_t s;

	sigemptyset(&s);
	printf("SIGUSR1 in set: %d\n", 	sigismember(&s, SIGUSR1));

	sigfillset(&s);
	printf("SIGUSR1 in set: %d\n", 	sigismember(&s, SIGUSR1));

	sigemptyset(&s);
	printf("SIGUSR1 in set: %d\n", 	sigismember(&s, SIGUSR1));

	sigaddset(&s, SIGUSR1);
	printf("SIGUSR1 in set: %d\n", 	sigismember(&s, SIGUSR1));

	sigdelset(&s, SIGUSR1);
	printf("SIGUSR1 in set: %d\n", 	sigismember(&s, SIGUSR1));
}/*main*/
