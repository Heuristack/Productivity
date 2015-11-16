 /**
 * TITLE: Incorrect use of pthread_exit argument
 * AUTHOR: LiYing
 * DATE: 2010-9-4 23:43:19
 * NOTE:
 */

#include<pthread.h>
#include<stdio.h>

struct foo {
	int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp){
    printf("%s", s);
    printf("  structure at 0x%x\n", (unsigned)fp);
    printf("  foo.a = %d\n", fp->a);
    printf("  foo.b = %d\n", fp->b);
    printf("  foo.c = %d\n", fp->c);
    printf("  foo.d = %d\n", fp->d);
}/*printfoo:returns:void*/

void *thr_fn1(void *arg){
	struct foo foo = {1, 2, 3, 4};

	printfoo("thread 1: \n", &foo);
	pthread_exit((void *)&foo);
}/*thr_fn1:returns:*/

void *thr_fn2(void *arg){
	printf("thread 2: ID is %d\n", pthread_self());
	pthread_exit((void *)0);
}/*thr_fn2:returns:*/

int main(int argc, char *argv[]){
	int err = 0;
	pthread_t tid1, tid2;
	struct foo *fp;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	err = pthread_join(tid1, (void *)&fp);
	sleep(1);

	printf("parent starting second thread\n");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	sleep(1);

	printfoo("parent:\n", fp);
	exit(0);
}/*main*/

