/**
 * TITLE: signal Function
 * AUTHOR: LiYing
 * DATE: 2010-5-13 16:05:34
 * NOTE:
 */
/**
 * SIGNAL HEADERS
 * #include<signal.h>
 * #include<sys/signal.h>
 * #include<bits/signum.h>
 * #include<sys/iso/signal_iso.h>
 */
/**
 * NULL SIGNAL
 * no signal has a signal number of 0
 * null signal
 */
/**
 * SIGNAL GENERATION CONDITIONS
 * 1.terminal-generated signals
 * 2.hardware exceptions generated signals
 * 3.kill(2) function allows a process to send any signal to another process or process group
 * 4.kill(1) command allows us to send signals to other processes
 * 5.software conditions can generate signals when something happens about which the process should be notified
 */
/**
 * DISPOSITION OF THE SIGNALS
 * 1.ignore the signal
 * 2.catch the signal
 * 3.let the default action apply
 */
/**
 * FUNCTION PROTOTYPE
 * #include<signal.h>
 * void (*signal(int signo, void (*func)(int)))(int);
 * return: previous disposition of signal if OK; SIG_ERR on error
 */
/**
 * ARGUMENTS
 * signo: signal name
 * func:
 * a. constant SIG_IGN: ignore the signal (we cannot ignore the two signals SIGKILL and SIGSTOP)
 * b. constant SIG_DEL: setting the action associated with the signal to its default value
 * c. the address of a function to be called when the signal occurs
 */
/**
 * Declarations in system header <signal.h>
 * #define SIG_ERR (void (*)())-1
 * #define SIG_DFL (void (*)())0
 * #define SIG_IGN (void (*)())1
 */
/**
 * PROBLEM -- unreliable-signals
 * The signal function is defined by ISO C, which doesn't involve multiple processes, process groups, terminal I/O, and the like.
 * Therefore, its definition of signals is vague enough to be almost useless for UNIX systems.
 * Implementations derived from UNIX System V support the signal function, but it provides the old unreliable-signal semantics.
 */
/**
 * SIGNAL HANDLER (SIGNAL CATCHING FUNCTION)
 *
 */
/**
 * PROGRAM START-UP
 *
 */
/**
 * PROCESS CREATION
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

static void sig_usr(int);

int main(int argc, char *argv[]){
	if (signal(SIGUSR1, sig_usr) == SIG_ERR){
		printf("register sig_usr for SIGUSR1 fail\n");
	}/*register sig_usr for SIGUSR1*/
	else if (signal(SIGUSR2, sig_usr) == SIG_ERR){
		printf("register sig_usr for SIGUSR1 fail\n");
	}/*register sig_usr for SIGUSR2*/
	for (;;)
		pause();
}/*main*/

static void
sig_usr(int signo){
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else{
		printf("received signal %d\n", signo);
		exit(1);
	}/*else*/
}/*sig_usr*/

