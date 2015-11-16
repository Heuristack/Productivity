/**
 * SUBJECT: Process Termination - 'exit' functions
 * AUTHOR: LiYing
 * TIME: 2009-10-20 18:47:23
 */
/**
 * TERMINATION STATUS VS EXIT STATUS
 * 1. kernel converts 'exit status' to 'termination status' when _exit is called.
 * 2. exit statis is the argument to 'exit' functions
 * 3. parent examine the termination status using macros
 * 4. parent can obtain the 'exit status' of child which terminated normally
 * 5. parent can obtain the 'termination status' of child in any case using waipid
 * 6. kernel closes all open discriptors, release memory regardless of how process terminates
 */
/**
 * MACROS TO EXAMINE TERMINATION STATUS (returned by wait and waitpid)
 * WIFEXITED(status):   1.True, if terminated normally;
 * 					    2.WEXITSTATUS(status) fetch the low-order 8 bits of the argument that child pass to 'exit'
 * WIFSIGNALED(status): 1.True, if terminated abnormally;
 *                      2.WTERMSIG(status) fetch signal number that caused the termination;
 *                      3.WCOREDUMP(status) see whether core file of the terminated process was generated;
 * WIFSTOPPED(status):  1.True, if child is currently stopped;
 *						2.WSTOPSIG(status) fetch signal number that caused the child to stop;
 * WIFCONTINUED(status):1.True, if child continued after a stop;
 */
/**
 * INHERITED BY INIT
 * 1.parent terminated before child
 * 2.guarante every process has a parent
 * 3.never be a zombie
 */
/**
 * CHILD TERMINATED FIRST
 * 1.child terminated before parent
 * 2.kernel keep a small amount of information for every terminated process
 * 3.keep: process id, termination status, amount of CPU time;
 * 4.discard: memory, open files;
 * 4.zombie: process terminated && parent not wait for it.
 * 5.If we write a long-running program that forks many child processes,
 *   they become zombies unless we wait for them and fetch their termination status.
 */

#include<stdio.h>
#include<stdlib.h>

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
}/*main*/
