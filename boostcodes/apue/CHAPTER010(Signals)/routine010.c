/**
 * SUBJECT: alarm and pause functions -- SLEEP IMPLEMENTATION
 * AUTHOR: LiYing
 */
/**
 * SLEEP1 PROBLEMS
 * 1.If the caller already has an alarm set, that alarm is erased by the first call to alarm;
 * 2.We have modified the disposition for SIGALRM;
 * 3.There is a race condition between the first call to alarm and the call to pause;
 */

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<setjmp.h>

static void sig_alarm(int signo){
	;
}/*sig_alarm*/

unsigned int sleep1(unsigned int nsecs){
	if (signal(SIGALRM, sig_alarm) == SIG_ERR)
		return (nsecs);
	alarm(nsecs);
	pause();
	return (alarm(0));
}/*sleep1*/

static jmp_buf env_alarm;

static void sig_alarm2(int signo){
	longjmp(env_alarm, 1);
}/*sig_alarm2*/

unsigned int sleep2(unsigned int nsecs){
	if (signal(SIGALRM, sig_alarm2) == SIG_ERR)
		return (nsecs);
	if (setjmp(env_alarm) == 0){
		alarm(env_alarm);
		pause();
	}/*setjmp*/
	return (alarm(0));
}/*sleep2*/

main(){}/*main*/
