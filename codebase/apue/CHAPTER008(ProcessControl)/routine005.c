/**
 * SUBJECT: Process Termination - 'wait' functions
 * AUTHOR: LiYing
 * TIME: 2009-10-20 18:47:23
 */
/**
 * FUNCTION PROTOTYPE -- wait for child process to stop or terminate
 * #include<sys/wait.h>
 * pid_t wait(int *status);
 * pid_t waitpid(pid_t pid, int statloc, int options);
 * returns: process id if OK, zero(), one on error
 */
/**
 * SIGCHLD SIGNAL (asynchronous notification)
 * 1.when process terminated either normally or abnormally
 * 2.send signal SIGCHLD to its parent
 * 3.parent ignore(default) or call signal handler
 * 4.options(??)
 */
/**
 * a process call wait or waitpid can
 * 1.block: all children are running;
 * 2.return immediately with termination status of a child: a process terminated & waiting for termination status to be fetched
 * 3.return immediately with an error: having no child process
 */
/**
 * wait vs waitpid (differences)
 * 1.wait block the caller until a child process(the first process) terminates;
 * 2.waitpid has an option to prevents the caller from blocking;
 * 3.waitpid doesn't wait for the child terminates first;
 * 4.waitpid has a number of options to control which process it waits for.
 */
/**
 * pid argument of waitpid
 * 1.pid == -1: wait for any child process
 * 2.pid >  0 : wait for process whose id equals to pid
 * 3.pid == 0 : wait fot any child process whose group id is equal to the calling process
 * 4.pid <  -1: wait for ayy child process whose group id is equal to the absolute value of pid
 */
/**
 * error of waipid
 * 1.process dose not exist
 * 2.process group does not exist
 * 3.process is not the child of the calling process
 */
/**
 * options constants of waitpid
 * WCONTINUED:1.The waitpid() function shall report the status of any continued child process
 *			  2.specified by pid whose status has not been reported
 *			  3.since it continued from a job control stop.
 * WNOHANG:   1.Not block if the 'pid' child is not immediately available;2.return 0;
 * WUNTRACED: 1.The status of any child processes specified by pid that are stopped, and
 *			  2.whose status has not yet been reported since they stopped,
 *            3.shall also be reported to the requesting process.
 */
/**
 * three features of waitpid
 * 1.waitpid provide waiting for one particular process
 * 2.waitpid provide a nonblocking version of wait
 * 3.waitpid provide support for job control
 */

#include<stdio.h>
#include<sys/wait.h>

void pr_exit(int status){
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d\n", WTERMSIG(status),
#ifdef WCOREDUMP
		WCOREDUMP(status) ? " (core file generated)" : "");
#else
		"");
#endif
	else if (WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}/*pr_exit*/

int main(int argc, char *argv[]){
	pid_t pid;
	int status;

	if ((pid = fork()) < 0){
		printf("fork error\n");
		return -1;
	}/*fork fail*/
	else if (pid == 0)
		exit(7);

	if (wait(&status) == pid)
		pr_exit(status);

	if ((pid = fork()) < 0){
		printf("fork error\n");
		return -1;
	}/*fork fail*/
	else if (pid == 0)
		abort();

	if (wait(&status) == pid)
		pr_exit(status);

	if ((pid = fork()) < 0){
		printf("fork error\n");
		return -1;
	}/*fork fail*/
	else if (pid == 0)
		status /= 0;		/*can't pass compiler checking*/

	if (wait(&status) == pid)
		pr_exit(status);
	exit(0);
}/*main*/

