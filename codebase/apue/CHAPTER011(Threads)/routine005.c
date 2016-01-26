 /**
 * TITLE: Fetching the thread exit status
 * AUTHOR: LiYing
 * DATE: 2010-9-4 23:38:00
 * NOTE:
 */

#include<pthread.h>
#include<stdio.h>

void *thr_fn1(void *arg){
	printf("thread 1 returning\n");
    return((void *)1);
}/*thr_fn1:return:*/

void *thr_fn2(void *arg){
	printf("thread 2 exiting\n");
	pthread_exit((void *)2);
}/*thr_fn2:return:*/

int main(int argc, char *argv[]){
	int err;
	pthread_t tid1, tid2;
	void *tret;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	err = pthread_join(tid1, &tret);
	printf("thread 1 exit code %d\n", (int)tret);
	err = pthread_join(tid2, &tret);
	printf("thread 2 exit code %d\n", (int)tret);

	exit(0);
}/*main*/
