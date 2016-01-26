/**
 * TITLE: Unreliable Signals
 * AUTHOR: LiYing
 * DATE: 2010-5-13 16:07:11
 * NOTE: 1."some code that isn't right, yet it works most of the time"; 2.signal action reset to default;
 */
/**
 * UNRELIABLE SIGNALS
 * 1.signals could get lost: a signal could occur and the process would never know about it (OK)
 * 2.process has little control over a signal: a process could catch a signal or ignore it	(OK)
 * 3.sometimes tell the kernel to block a signal: don't ignore it, just remember if it occurs, and tell us later when we're ready (NO)
 */
/**
 * One problem with these early versions is that the action for a signal was reset to its default each time the signal occurred
 *
 */

#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<sys/signal.h>

int sig_int_flag = 0;

int main(){
	void sig_int(int);
	signal(SIGINT, sig_int);

	while (sig_int_flag == 0) {
		/**
		 * this is the point where problems can occur
		 *
		 */
		pause();
	} /*main-loop*/

	return 0;
}/*main*/

void sig_int(int sig){
	signal(SIGINT, sig_int);					/*reinstall the signal handler because of the automatically resetting signal handler to defalt*/
	printf("sig_int: received signal%d\n", sig);
	printf("sig_int: %s\n", strsignal(sig));
	psignal(sig, "sig_int");
	sig_int_flag = 1;
}/*sig_int*/
