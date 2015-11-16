/**
 * TITLE: Synchronous signal handling
 * AUTHOR: LiYing
 * DATE: 2010-9-10 15:54:26
 * NOTE:
 */

#include<pthread.h>

int  quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	wait = PTHREAD_COND_INITIALIZER;

void *thr_fn(void *arg){	//blocked to wait a signal
	int err, signo;
	for ( ; ; ){
		err = sigwait(&mask, &signo);			//sigwait
		switch (signo){
			case SIGINT:
				printf("interrupt\n");
				break;
			case SIGQUIT:
				pthread_mutex_lock(&lock);
				quitflag = 1;
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&wait);
				return (0);
				break;
			default:
				printf("unexcepted signal %d\n", signo);
				exit(1);
		}/*switch*/
	}/*infinite-loop*/
}/*returns:pointer*/

int main(void){
	int err;
	sigset_t oldmask;
	pthread_t tid;

	sigemptyset(&mask);
	sigaddset(SIGINT, &mask);
	sigaddset(SIGQUIT, &mask);

	pthread_sigmask(SIG_BLOCK, &mask, &oldmask);

	pthread_create(&tid, NULL, thr_fn, 0);

	pthread_mutex_lock(&lock);
	while (quitflag == 0)
		pthread_cond_wait(&wait, &lock);
	pthread_mutex_unlock(&lock);
	quitflag = 0;

	sigprocmask(SIG_SETMASK, &oldmask, NULL);

	exit(0);
}/*main:*/

