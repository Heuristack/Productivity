/**
 * SUBJECT: Process Creation -- vfork
 * AUTHOR: LiYing
 * TIME: 2009-10-20 17:15:26
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * 		pid_t fork(void);
 * returns: 0 in child, process id of child in parent; -1 on error
 */
/**
 * RELATION WITH FORK
 * 1.spawn new process (just like fork)
 * 2.share virtual memory (without copying the address space of the parent into the child)
 * 3.a higher performance optimization (on paged virtual-memory implementations)
 * 4.guarantees child runs first, until child calls exec or exit (synchronization)
 */
/**
 * RUNNING RESULTS COMPARISON
 * before fork
 * pid = 5898, global = 6, aotovar = 88
 * before vfork
 * pid = 17937, global = 7, aotovar = 89
 */
#include<stdio.h>
#include<unistd.h>

int global = 6;

int main(int argc, char *argv[]){
	int aotovar;
	pid_t pid;

	aotovar = 88;
	printf("before vfork\n");

	if ((pid = vfork()) < 0){
		printf("fork error\n");
		exit(1);
	}/*fork fail*/
	else if (pid == 0){
		global++;
		aotovar++;
		_exit(0);
	}/*child*/
	printf("pid = %d, global = %d, aotovar = %d\n", getpid(), global, aotovar);
	exit(0);
}/*main*/
