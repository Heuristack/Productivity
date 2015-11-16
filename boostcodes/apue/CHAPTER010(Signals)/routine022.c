/**
 * TITLE: Routines to allow a parent and child to synchronize
 * AUTHOR: LiYing
 * DATE: 2010-5-26 20:09:52
 * NOTE:
 */
/**
 * FUNCTION PROTOTYPE -- sigsuspend
 * #include<signal.h>
 * int sigsuspend(const sigset_t *sigmask);
 * returns: minus one with errno set to EINTR
 */
/**
 * REMARKS
 * The signal mask of the process is set to the value pointed to by sigmask.
 * Then the process is suspended until a signal is caught or until a signal occurs that terminates the process.
 * If a signal is caught and if the signal handler returns, then sigsuspend returns, and
 * the signal mask of the process is set to its value before the call to sigsuspend.
 */
/**
 * EXAMPLE3 -- routines to allow a parent and child to synchronize
 *
 */
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo){
	sigflag = 1;
}/*sig_usr*/

void TELL_WAIT(void){
	if (signal(SIGUSR1, sig_usr) == SIG_ERR){
		printf("main: call signal failed\n");
		exit(1);
	}/*signal usr1*/
	if (signal(SIGUSR2, sig_usr) == SIG_ERR){
		printf("main: call signal failed\n");
		exit(1);
	}/*signal usr2*/
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		printf("main: call sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/
}/*TELL_WAIT*/

void TELL_PARENT(pid_t pid){
	kill(pid, SIGUSR2);
}/*TELL_PARENT*/

void WAIT_PARENT(void){
	while(sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 0;

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		printf("main: call sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/
}/*WAIT_PARENT*/

void TELL_CHILD(pid_t pid){
	kill(pid, SIGUSR1);
}/*TELL_CHILD*/

void WAIT_CHILD(void){
	while(sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 0;

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		printf("main: call sigprocmask failed\n");
		exit(1);
	}/*sigprocmask*/
}/*WAIT_CHILD*/

int main(int argc, char *argv[]){
	pid_t pid;

	TELL_WAIT();
	pid = fork();
	if (pid < 0)
		perror("fork failed\n");
	else if (pid > 0){		/*parent*/
		printf("parent: wait child ... \n");
		WAIT_CHILD();
		printf("parent: waited child exit\n");
		exit(1);
	}/*parent*/
	else if (pid == 0){		/*child*/
		printf("child: sleep 3 seconds ... \n");
		sleep(3);
		printf("child: wakes up & tell parent \n");
		TELL_PARENT(getppid());
		exit(1);
	}/*child*/
}/*main*/
