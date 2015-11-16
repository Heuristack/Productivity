/**
 * TITLE: Correct POSIX.1 implementation of system function
 * AUTHOR: LiYing
 * DATE: 2010-5-28 10:41:15
 * NOTE:
 */
/**
 * FUNCTION PROTOTYPE
 * #include<stdlib.h>
 * int system(const char *cmdstring);
 * returns:
 * (1) -1 with errno set to indicate the error
 * (2) as if shell executes exit(127)
 * (3) termination status of the shell
 */

/**
 * IMPLEMENTATION -
 * Correct POSIX.1 implementation of system function
 */

#include<unistd.h>
#include<signal.h>
#include<errno.h>
#include<sys/wait.h>

int mysystem(const char *cmdstring){	/* with appropriated signal handling */
	pid_t pid;
	int status;
	struct sigaction ignore, saveintr, savequit;
	sigset_t chldmask, savemask;

	ignore.sa_handler = SIG_IGN;
	ignore.sa_flags = 0;
	sigemptyset(&ignore.sa_mask);
	if (sigaction(SIGINT, &ignore, &saveintr) < 0)
		return (-1);
	if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
		return (-1);

	sigemptyset(&chldmask);
	sigaddset(&chldmask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
		return (-1);

	pid = fork();
	if (pid < 0)
		status = -1;
	else if (pid > 0){		/*parent*/
		while (waitpid(pid, &status, 0) < 0)
			if (errno == EINTR) {
				status = -1;
				break;
			}/*wait interrupted*/
	}/*parent*/
	else if (pid == 0){		/*child*/
		sigaction(SIGINT, &saveintr, NULL);
		sigaction(SIGQUIT, &savequit, NULL);
		sigprocmask(SIG_SETMASK, &savemask, NULL);

		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		_exit(127);
	}/*child*/

	sigaction(SIGINT, &saveintr, NULL);
	sigaction(SIGQUIT, &savequit, NULL);
	sigprocmask(SIG_SETMASK, &savemask, NULL);

	return (status);
}/*system*/

main(){
	int result;
	result = mysystem("date > file");
	printf("main:mysystem return value=%d; errno=%d\n", result, errno);
}/*main*/
