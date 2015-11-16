/**
 * SUBJECT: Error Logging
 * AUTHOR: LiYing
 */
/**
 * FUNCTION PROTOTYPE
 * #include<syslog.h>
 * void openlog(const char *ident, int option, int facility);
 * void syslog(int priority, const char *format, ...);
 * void closelog(void);
 * int setlogmask(int maskpri);
 * returns: previous log priority mask value
 */
/**
 * FUNCTION PROTOTYPE
 * #include<syslog.h>
 * #include<stdarg.h>
 * void vsyslog(int priority, const char *format, va_list arg);
 */
/**
 * OPENLOG OPTION ARGUMENT -- BITMASK
 * LOG_CONS
 * LOG_NDELAY
 * LOG_NOWAIT
 * LOG_ODELAY
 * LOG_PERROR
 * LOG_PID
 */
/**
 * OPENLOG FACILITY ARGUMENT || SYSLOG PRIORITY ARGUMENT
 * LOG_AUTH			authorization programs
 * LOG_AUTHPRIV		same as LOG_AUTH, but logged to file with restricted permissions
 * LOG_CRON			cron and at
 * LOG_DAEMON		system daemons
 * LOG_FTP			ftp daemon
 * LOG_KERN			message generated by the kernel
 * LOG_LOCAL0		reserved for local use
 * LOG_LOCAL1
 * LOG_LOCAL2
 * LOG_LOCAL3
 * LOG_LOCAL4
 * LOG_LOCAL5
 * LOG_LOCAL6
 * LOG_LOCAL7
 * LOG_LPR
 * LOG_MAIL
 * LOG_NEWS
 * LOG_SYSLOG		the syslogd daemon itself
 * LOG_USER
 * LOG_UUCP
 */
/**
 * SYSLOG PRIORITY ARGUMENT
 * LOG_EMERG		emergency
 * LOG_ALERT		condition that must be fixed immediately
 * LOG_CRIT			cirtical condition
 * LOG_ERR			error condition
 * LOG_WARNING		warning condition
 * LOG_NOTICE		normal, but significant condition
 * LOG_INFO			informational message
 * LOG_DEBUG		debug message
 */
/**
 * Where the log is written?
 * /etc/syslog.conf
 * /var/adm/syslog/syslog.log
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
	daemonize("liying");
	sleep(3);
	syslog(LOG_USER | LOG_INFO, "hello, system daemon log system");
}/*main*/
