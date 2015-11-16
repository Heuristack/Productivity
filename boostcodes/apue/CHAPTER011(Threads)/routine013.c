/**
 * TITLE: Creating a thread in the detached state
 * AUTHOR: LiYing
 * DATE: 2010-9-8 21:05:03
 * NOTE:
 */

#include<pthread.h>

int makethread(void *(*fn)(void *), void *arg){
	int				err;
	pthread_t 		tid;
	pthread_attr_t	attr;

	err = pthread_attr_init(&attr);
	if (err != 0)
		return (err);
	err = phtread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (err == 0)
		err = pthread_create(&tid, &attr, fn, arg);
	err = pthread_attr_destory(&attr);
	return (err);
}/*makethread:returns:*/

