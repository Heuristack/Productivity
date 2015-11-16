/**
 * TITLE: Another (imperfect) implementation of sleep
 * AUTHOR: LiYing
 * DATE: 2010-5-17 8:51:58
 * NOTE:
 */
#include<setjmp.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

static jmp_buf env_alrm;

static void sig_int(int signo){
	int i, j;
	volatile int k;
	printf("\nsig_int starting\n");
	for (i = 0; i < 300000; i++)
		for (j = 0; j < 4000; j++)
			k += i*j;
	printf("sig_int finished\n");
}/*sig_int*/

void sig_alrm(int signo){
	longjmp(env_alrm, 1);
}/*sig_alrm*/

unsigned int sleep2(unsigned int nsecs){
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return nsecs;
	if (setjmp(env_alrm) == 0) {
		alarm(nsecs);		/*start the timer*/
		pause();			/*next caught signal wakes up*/
	} /*if-1stjmp-lable*/
	return (alarm(0));
}/*sleep2*/

int main(int argc, char *argv[]){
	unsigned int unslept;
	if (signal(SIGINT, sig_int) == SIG_ERR) {
		perror("signal install failed\n");
		exit(1);
	} /*if-signal-error*/
	unslept = sleep2(20);
	printf("sleep2 returned: %u\n", unslept);
	printf("sleep2 returned with pause interrupted: %s\n", strerror(errno));
	perror("sleep2 returned with pause interrupted");
	exit(0);
}/*main*/
