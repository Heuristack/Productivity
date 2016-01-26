/**
 * SUBJECT: Orphaned Process Groups
 * AUTHOR: LiYing
 */
/**
 * SCENARIO
 * a process has forked a child that stops, and
 * the parent is about to exit.
 */
/**
 * STEPS:
 * 1.The parent sleeps for 5 seconds
 * 2.The child establishes a signal handler for the hang-up signal (SIGHUP).
 * 3.The child sends itself the stop signal (SIGTSTP) with the kill function.
 * 4.When the parent terminates, the child is orphaned, so the child's parent process ID becomes 1, the init process ID.
 * 5.At this point, the child is now a member of an orphaned process group
 * 6.Since the process group is orphaned when the parent terminates, POSIX.1 requires that
 *   every process in the newly orphaned process group that is stopped (as our child is) be sent the hang-up signal (SIGHUP)
 *   followed by the continue signal (SIGCONT).
 * 7.This causes the child to be continued, after processing the hang-up signal.
 */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>


static void sig_hup(int signo){
	printf("SIGHUP receieve, pid=%d\n", getpid());
}/*sig_hup*/

static void print_ids(char *name){
	printf("%s, pid=%d, ppid=%d, pgrp=%d, tpgrp=%d\n", name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}/*print_ids*/

int main(void){
	char c;
	pid_t pid;

	print_ids("parent");
	if ((pid = fork()) < 0){
		printf("main: fork failed\n");
		exit(0);
	}/*fork failed*/
	else if (pid > 0){
		sleep(5);
		exit(0);
	}/*parent*/
	else {
		print_ids("child");
		signal(SIGHUP, sig_hup);
		kill(getpid(), SIGTSTP);
		print_ids("child");
		if (read(STDIN_FILENO, &c, 1) != 1)
			printf("read error from controlling TTY, errno = %d\n", errno);
		exit(0);
	}/*child*/
}/*main*/

/**
 * parent, pid=4022, ppid=21660, pgrp=4022, tpgrp=4022
 * child, pid=4024, ppid=4022, pgrp=4022, tpgrp=4022
 * SIGHUP receieve, pid=4024
 * child, pid=4024, ppid=1, pgrp=4022, tpgrp=4022
 * read error from controlling TTY, errno = 5
 */
