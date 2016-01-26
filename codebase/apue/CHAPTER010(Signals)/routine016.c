/**
 * SUBJECT: signal names && signal mappings
 * AUTHOR: LiYing
 */

/**
 * EXTERNAL VARIABLES
 * extern char *sys_siglist[];
 */
/**
 * FUNCTION PROTOTYPE -- signal names
 * #include<signal.h>
 * void psignal(int signo, const char *msg);
 * returns:
 *
 * #include<string.h>
 * char *strsignal(int signo);
 * returns: a pointer to a string descriping the signal
 */
/**
 * FUNCTION PROTOTYPE -- signal mappings
 * #include<signal.h>
 * int sig2str(int signo, char *str);
 * int str2sig(const char *str, int *signop);
 * returns: zero if OK, minus one on error
 */
#include<stdio.h>
#include<signal.h>
#include<string.h>

int main(){
	psignal(SIGABRT	, "SIGABRT");
	psignal(SIGALRM	, "SIGALRM");
	psignal(SIGBUS	, "SIGBUS");
	psignal(SIGCHLD	, "SIGCHLD");
	psignal(SIGCONT	, "SIGCONT");
	psignal(SIGFPE	, "SIGFPE");
	psignal(SIGHUP	, "SIGHUP");
	psignal(SIGILL	, "SIGILL");
	psignal(SIGINT	, "SIGINT");
	psignal(SIGKILL	, "SIGKILL");
	psignal(SIGPIPE	, "SIGPIPE");
	psignal(SIGQUIT	, "SIGQUIT");
	psignal(SIGSEGV	, "SIGSEGV");
	psignal(SIGSTOP	, "SIGSTOP");
	psignal(SIGTERM	, "SIGTERM");
	psignal(SIGTSTP	, "SIGTSTP");
	psignal(SIGTTIN	, "SIGTTIN");
	psignal(SIGTTOU	, "SIGTTOU");
	psignal(SIGURG	, "SIGURG");
	psignal(SIGUSR1	, "SIGUSR1");
	psignal(SIGUSR2	, "SIGUSR2");
	return 0;
}/*main*/

