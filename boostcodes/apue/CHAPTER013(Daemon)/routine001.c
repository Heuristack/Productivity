/**
 * SUBJECT: Daemons
 * AUTHOR: LiYing
 */
/**
 * Daemons Coding Rules
 * Some basic rules to coding a daemon prevent unwanted interactions from happening.
 * 1.Call umask to set the file mode creation mask to 0.
 * 2.Call fork and have the parent exit.
 * 3.Call setsid to create a new session.
 * 4.Change the current working directory to the root directory.
 * 5.Unneeded file descriptors should be closed.
 * 6.Some daemons open file descriptors 0, 1, and 2 to /dev/null so that
 *   any library routines that try to read from standard input or write to standard output or standard error will have no effect
 */

#include<stdio.h>
#include<fcntl.h>
#include<signal.h>
#include<syslog.h>
#include<sys/resource.h>

void daemonize(const char *cmd){

	/**
	 * Daemonizing Rule01:
	 * Clear file creation mask.
	 */
	umask(0);

	/**
	 * Daemonizing Rule02:
	 * Get max number of file descriptors
	 */
	struct rlimit rl;
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0){
		printf("%s: get file num limit failed\n", cmd);
		exit(1);
	}/*get resource limit*/

	/**
	 * Daemonizing Rule03:
	 * Become a session leader to lose controlling TTY
	 */
	pid_t pid;
	if ((pid = fork()) < 0){
		perror("daemonize: fork failed");
		exit(1);
	}/*fork failed*/
	else if (pid != 0)
		exit(0);
	else
		setsid();

	/**
	 * Daemonizing Rule04:
	 * Ensure future opens won't allocate controlling TTYs
	 */
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0){
		perror("daemonize: sigaction failed");
		exit(1);
	}/*sigaction*/
	else if ((pid = fork()) < 0){
		perror("daemonize: fork failed");
		exit(1);
	}/*fork failed*/
	else if (pid != 0){
		exit(0);
	}/*parent*/

	/**
	 * Daemonizing Rule05:
	 * Change the current working directory to root so
	 * we won't prevent file systems from being unmounted.
	 */
	if (chdir("/") < 0){
		perror("daemonize: can't change working directory to /");
		exit(1);
	}/*chdir*/

	/**
	 * Daemonizing Rule06:
	 * Close all open files descriptors.
	 */
	int i;
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	/**
	 * Daemonizing Rule07:
	 * Attach file descriptors 0, 1 and 2 to /dev/null.
	 */
	int fd0, fd1, fd2;
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	/**
	 * Daemonizing Rule08:
	 * Initialize the log file.
	 */
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2){
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}/*syslog*/
}/*daemonize*/

main(){
	daemonize("daemonize:");
	sleep(5);
}/*main*/
