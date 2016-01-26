/**
 * TITLE: Reentrant Functions
 * AUTHOR: LiYing
 * DATE: 2010-5-14 9:38:03
 * NOTE: 1.nonreentrant functions can not be called in signal handlers;
 */
/**
 * REENTRANT FUNCTIONS
 * interrupted function && the signal handler
 * instructions sequence of the function call
 */
/**
 * NONREENTRANT FUNCTIONS CATEGROIES
 * (a)use static data structures
 * (b)call malloc or free (use linked-list)
 * (c)part of the standard I/O libary (use global data-structure)
 */
/**
 * NOTES:
 * Most implementations of the standard I/O library use global data structures in a nonreentrant way.
 * Note that even though we call printf from signal handlers in some of our examples, it is not guaranteed
 * to produce the expected results, since the signal hander can interrupt a call to printf from our main program.
 */
/**
 * LONGJMP && SIGLOMGJMP
 * updating a data structure in a nonreentrant way
 */

#include<stdio.h>
#include<stdlib.h>
#include<pwd.h>
#include<signal.h>

static void my_alarm(int signo){
	struct passwd *rootptr;

	/**
	 * window here could cause problem
	 * because of the automatic signal-handler resetting
	 *
	 */
	signal(SIGALRM, my_alarm);
	printf("in signal handler\n");
	if ((rootptr = getpwnam("root")) == NULL){
		printf("getpwnam(root) error\n");
		exit(1);
	}/*getpwnam*/
	alarm(1);
}/*my_alarm*/

int main(void){
	struct passwd *ptr;

	signal(SIGALRM, my_alarm);
	alarm(1);
	for(;;){
		if ((ptr = getpwnam("atiifas")) != NULL){
			/**
			 * point problem could happened
			 * because of getpwnam use global variables
			 * and it is not reentranted function
			 */
			if (strcmp(ptr->pw_name, "atiifas") != 0){
				printf("return values corrupted!, pw_name = %s\n", ptr->pw_name);
			}/*string comparation*/
		}/*getpwnam*/
		else {
			printf("getpwnam error\n");
			exit(1);
		}/*error*/
	}/*for*/
}/*main*/
