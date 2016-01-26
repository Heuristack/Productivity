/**
 * TITLE: Simple, incomplete implementation of sleep
 * AUTHOR: LiYing
 * DATE: 2010-5-17 8:43:22
 * NOTE: 1.previous timer is erased; 2.disposition for SIGALRM has been modified;
 *		 3.race condition existed between calls to alarm and pause;[setjmp;sigprocmask & sigsuspend]
 */
#include<signal.h>
#include<unistd.h>

void sig_alrm(int sig){
	/*nothing to do, just return to wake up pause*/
}/*sig_alrm*/

unsigned int sleep1(unsigned int nsecs){
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return (nsecs);
	alarm(nsecs);			/*start the timer*/
							/*race condition may happened here*/
	pause();				/*next caught signal wakes up*/
	return alarm(0);		/*turn off the timer, return unslept time*/
}/*sleep1*/

int main(int argc, char *argv[]){

}/*main*/
