/**
 * TITLE: kill and raise functions
 * AUTHOR: LiYing
 * DATE: 2010-5-14 17:32:28
 * NOTE:
 */
/**
 * FUNCTION PROTOTYPE
 * #include<signal.h>
 * int kill(pid_t pid, int signo);
 * int raise(int signo);
 * returns: zero if OK, minus one on error
 */
/**
 * KILL
 * send a signal to a process or a group of processes.
 * pid > 0, send to process pid
 * pid = 0, send to pgrp
 * pid < 0, send to pgrp pid
 * pid = 1, send to all processes
 */
/**
 * RAISE
 * send a signal to oneself
 */
/**
 * PERMISSION RULES
 * (a)privilege: superuser can send a signal to any process;
 * (b)basic rule: the real or effective user ID of the sender has to equal the real or effective user ID of the receiver;
 * (c)special case: if the signal being sent is SIGCONT, a process can send it to any other process in the same session
 */
/**
 * NULL SIGNAL
 * If we send the process the null signal and it doesn't exist, kill returns 1 and errno is set to ESRCH.
 */
/**
 * KILL CAUSED SIGNAL
 * If the call to kill causes the signal to be generated for the calling process and
 * if the signal is not blocked, either signo or some other pending, unblocked signal is delivered to the process before kill returns.
 */

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

static void sig_usr(int signo){
	printf("really entry signal handler function\n");
	if (signo == SIGUSR1){
		printf("receieved SIGUSR1\n");
	}/*test*/
	printf("OK, left the signal handler function\n");
}/*sig_usr*/

int main(int argc, char *argv[]){
	signal(SIGUSR1, sig_usr);
	printf("before sender sending signal\n");
	raise(SIGUSR1);
	printf("after receiever receieve signal\n");
	exit(1);
}/*main*/
