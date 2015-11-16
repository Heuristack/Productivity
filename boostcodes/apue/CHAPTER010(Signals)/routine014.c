/**
 * TITLE: sigaction Function
 * AUTHOR: LiYing
 * DATE: 2010-5-17 20:11:38
 * NOTE:
 */
/**
 * FUNCTION PROTOTYPE
 * #include<signal.h>
 * int sigaction(
 * 		int signo,
 * 		const struct sigaction *restrict act,
 * 		struct sigaction *restrict oact,
 * );
 * returns: zero if OK, minus one on error
 */
/**
 * SIGACTION STRUCTURE
 * struct sigaction {
 * 		void  	 (* sa_handler)(int);
 * 		sigset_t	sa_mask;
 * 		int			sa_flags;
 *		void  	 (* sa_sigaction)(int, siginfo_t *, void *);
 * };
 */
/**
 * ARGUMENT SA_FLAGS:
 * SA_INTERRUPT | SA_NOCLDSTOP | SA_NOCLDWAIT
 * SA_NODEFER | SA_ONSTACK | SA_RESETHAND
 * SA_RESTART | SA_SIGINFO
 */

/**
 * TWO FORMS OF SIGNAL HANDLERS:
 * FORM1:
 * 		void handler(int signo);
 * FORM2:(SA_SIGINFO IS SET)
 * 		void handler(int signo, siginfo_t *info, void *context);
 */
/**
 * SIGINFO STRUCTURE
 * struct siginfo {
 * 		int		si_signo;		//signal number
 * 		int 	si_errno;		//if nozero, errno value from <errno.h>
 * 		int 	si_code;		//additional info (depends on signal)
 *		pid_t	si_pid;			//sending process ID
 * 		uid_t	si_uid;			//sending process real user ID
 *		void   *si_addr;		//address that cause the fault
 * 		int		si_status;		//exit value or signal number
 * 		long 	si_band;		//bind number for SIGPOLL
 * };
 */

int main(){}/*main*/

