/**
 * TITLE: SIGCLD semantics
 * AUTHOR: LiYing
 * DATE: 2010-5-14 17:30:57
 * NOTE: (b) will cause system stack overflows
 */
/**
 * SIGCLD/SIGCHLD Semantics
 * (a)If the process specifically sets its disposition to SIG_IGN,
 *    children of the calling process will not generate zombie processes;
 * (b)If we set the disposition of SIGCLD to be caught, the kernel immediately checks whether
 *    any child processes are ready to be waited for and, if so, calls the SIGCLD handler;
 */

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>

static void sig_cld(int);

int main(){
	pid_t pid;

	if (signal(SIGCLD, sig_cld) == SIG_ERR)
		perror("signal error");
	pid = fork();
	if (pid < 0)
		perror("fork failed\n");
	else if (pid > 0){		/*parent*/
		pause();
	}/*parent*/
	else if (pid == 0){		/*child*/
		sleep(2);
		_exit(0);
	}/*child*/
}/*main*/

static void sig_cld(int signo){
	pid_t pid;
	int status;

	printf("SIGCLD received\n");
	if (signal(SIGCHLD, sig_cld) == SIG_ERR)
		perror("signal error");
	if ((pid = wait(&status)) < 0)
		perror("wait error");
	/**
	 * signal handler should be added here
	 *
	 */
	printf("pid = %d\n", pid);
}/*sig_cld*/
