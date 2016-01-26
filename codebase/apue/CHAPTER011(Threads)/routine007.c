 /**
 * TITLE: Thread cleanup handler
 * AUTHOR: LiYing
 * DATE: 2010-9-6 9:06:25
 * NOTE:
 */

#include<pthread.h>
#include<stdio.h>

void cleanup(void *arg){
	printf("cleanup: %s\n", arg);
}/*cleanup*/

void *thr_fn1(void *arg){
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");
	if (arg)
		return ((void *)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return ((void *)1);
}/*thr_fn1*/

void *thr_fn2(void *arg){
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	if (arg)
		pthread_exit((void *)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}/*thr_fn2*/

int main(int argc, char *argv[]){
	void *tret;
	pthread_t tid1, tid2;
	int err = 0;

	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);

	err = pthread_join(tid1, &tret);
	printf("thread 1 exit code %d\n", (int)tret);
	err = pthread_join(tid2, &tret);
	printf("thread 2 exit code %d\n", (int)tret);

	exit(0);
}/*main*/

