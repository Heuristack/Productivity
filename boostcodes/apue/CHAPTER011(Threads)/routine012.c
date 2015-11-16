/**
 * TITLE: Using condition variables
 * AUTHOR: LiYing
 * DATE: 2010-9-6 21:27:55
 * NOTE:
 */

#include<pthread.h>
#include<stdlib.h>

struct msg {
	struct msg *m_next;
};

struct msg workq;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void){
	struct msg *mp;
	while (1){
		pthread_mutex_lock(&qlock);
		while (workq == NULL)
			pthread_cond_wait(&qready, &qlock);
		mp = workq;
		workq = mp->m_next;
		pthread_mutex_unlock(&qlock);
	}/*processing-loop*/
}/*process_msg:returns:void*/

void enqueue_msg(struct msg *mp){
	pthread_mutex_lock(&qlock);
	mp->m_next = workq;
	workq = mp;
	pthread_mutex_unlock(&qlock);
	pthread_cond_signal(&qready);
}/*enqueue_msg:returns:void*/


int main(int argc, char *argv[]){
	exit(0);
}/*main*/
