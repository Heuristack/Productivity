/**
 * TITLE: pthread_atfork example
 * AUTHOR: LiYing
 * DATE: 2010-9-10 15:54:35
 * NOTE:
 */

#include<pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void){
	printf("prepare unlocking locks ...\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}/*prepare:returns:void*/

void parent(void){
	printf("parent unlocking locks ...\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}/*parent:returns:void*/

void child(void){
	printf("child unlocking locks ...\n");
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
}/*child:returns:void*/

void *thr_fn(void *arg){
	printf("thread started...\n");
	pause();
	return (0);
}/*thr_fn:returns:pointer*/

int main(void){
	int			err;
	pid_t 		pid;
	pthread_t	tid;

	pthread_atfork(prepare, parent, child);
	pthread_create(&tid, NULL, thr_fn, NULL);

	sleep(2);

	printf("parent abort to fork\n");
	if ((pid = fork()) == 0)
		printf("child returns from fork\n");

	printf("parent returns from fork\n");
	exit(0);
}/*main*/

