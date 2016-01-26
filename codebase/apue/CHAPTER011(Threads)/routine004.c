 /**
 * TITLE: Printing thread IDs
 * AUTHOR: LiYing
 * DATE: 2010-9-4 23:32:59
 * NOTE:
 */

#include<pthread.h>
#include<stdio.h>

pthread_t ntid;

void printids(const char *s){
	pid_t pid;
	pthread_t tid;		//structure or integer

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
      (unsigned int)tid, (unsigned int)tid);
}/*printids:returns:void*/

void *thr_fn(void *arg){
	printids("new thread: ");
	return ((void *)0);
}/*thr_fn:returns:*/

int main(int argc, char *argv[]){
	int err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0)
		fprintf(stderr, "can't create thread: %s\n", strerror(err));
	printids("main thread: ");
	sleep(1);
	exit(0);
}/*main*/
