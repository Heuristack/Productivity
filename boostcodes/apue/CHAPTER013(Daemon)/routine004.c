/**
 * SUBJECT: Daemons
 * AUTHOR: LiYing
 */

/**
 * DAEMON CONVENTIONS
 * (a) If the daemon uses a lock file, the file is usually stored as /var/run/name.pid
 * (b) If the daemon supports configuration options, they are usually stored in /etc/name.conf
 * (c) Daemons can be started from the command line, but they are usually started from one of the system initialization scripts (/etc/rc* or /etc/init.d/*).
 * (d) If a daemon has a configuration file, the daemon reads it when it starts, but usually won't look at it again.
 */

/**
 * EXAMPLE -- daemon rereading configuration files
 *
 */

#include<pthread.h>
#include<syslog.h>

sigset_t mask;

extern int already_running(void);

void reread(void){
	;
}/*reread*/

void *thr_fn(void *arg){
	int err, signo;

	for( ; ; ){
		err = sigwait(&mask, &signo);
		if (err != 0){
			syslog(LOG_ERR, "sigwait failed");
			exit(1);
		}/*sigwait failed*/

		switch (signo){
			case SIGHUP:
				syslog(LOG_INFO, "Re-reading configuration file");
				break;
			case SIGTERM:
				syslog(LOG_INFO, "got SIGTERM; exiting");
				break;
			default:
				syslog(LOG_INFO, "unexpected signal %d\n", signo);
				break;
		}/*switch*/

	}/*for*/
	return (0);
}/*thr_fn*/

int main(int argc, char *argv[]){
	int			 	 err;
	pthread_t		 tid;
	char			*cmd;
	struct sigaction sa;

	if ((cmd = strrchr(argv[0], '/')) == NULL)
		cmd = argv[0];
	else
		cmd++;

	/**
	 * Become a daemong
	 */
	daemonize(cmd);

	/**
	 * Make sure only one copy of the daemon is running
	 */
	if (already_running()){
		syslog(LOG_ERR, "daemon already running");
		exit(1);
	}/*daemon already running*/

	/**
	 * Restore SIGHUP default and block all signals
	 */
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flag = 0;
	if (sigaction(SIGHUP, sa, NULL)){
		syslog(LOG_ERR, "can't restore SIGHUP default");
		exit(1);
	}/*install signal handler*/
	sigfillset(&mask);
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0){
		syslog(LOG_ERR, "SIG_BLOCK error");
		exit(1);
	}/*thread sigmask*/

	/**
	 * Create a thread to handle SIGHUP and SIGTERM
	 */
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if (err != 0){
		syslog(LOG_ERR, "can't create thread");
		exit(1);
	}/*thread create error*/
	exit(0);
}/*main*/

