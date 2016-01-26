/**
 * TITLE: Using a recursive mutex
 * AUTHOR: LiYing
 * DATE: 2010-9-8 21:05:54
 * NOTE:
 */

#include<pthread.h>
#include<time.h>
#include<sys/time.h>

extern int makethread(void *(*fn)(void *), void *);

struct to_info {						//time out infomation
	void		  (*fn)(void *);		//function
	void 		   *to_arg;				//argument
	struct timespec to_wait;			//interval:tv_sec;tv_nsec;
};

#define	SECTONSEC	1000000000			//#define BILLION 	1000000000
#define USECTONSEC	1000				//#define THOUSAND	1000

void *timeout_helper(void *arg){		//timer to start up routine
	struct to_info *tip;
	tip = (struct to_info *)arg;
	nanosleep(&tip->to_wait, NULL);
	(*tip->to_fn)(tip->to_arg);
	return ((void *)0);
}/*timeout_helper:returns:*/

void timeout(const struct timespec *when, void (*func)(void *arg), void *arg){
	struct timespec now;		//time types: timespec{};timeval{};time_t
	struct timeval	tv;
	struct to_info *tip;
	int	err;

	gettimeofday(&tv, NULL);
	now.tv_sec = tv.tv_sec;
	now.tv_nsec = tv.tv_usec * USECTONSEC;

	if ((now.tv_sec < when.tv_sec) ||
		(now.tv_sec == when.tv_sec && now.tv_nsec < when.tv_nsec)){
		tip = malloc(sizeof(struct to_info));
		if (tip != NULL){
			tip->to_fn = func;
			tip->to_arg = arg;
			tip->to_wait.tv_sec = when.tv_sec - now.tv_sec;
			if (when->tv_nsec >= now->tv_nsec){
				tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
			}/*now(s,ns) <= when(s,ns)*/
			else {
				tip->to_wait.tv_sec--;			//(s, ns) = (s-1, ns+BILLION) when s >= 1
                tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
			}/*s(now) < s(when) && ns(now) > ns(when)*/
			err = makethread(timeout_helper, (void *)tip);
		}/*threaded*/
	}/*compute*/

	(*func)(arg);
}/*timeout:returns:void*/

pthread_mutex_t	mutex;
pthread_mutexattr_t	attr;

void retry(void *arg){
	pthread_mutex_lock(&mutex);
	/*retry*/
	pthread_mutex_unlock(&mutex);
}/*retry:returns:void*/

int main(int argc, char *argv[]){
	int err, condition, arg;
	struct timespec when;
	int err;
	err = pthread_mutexattr_init(&attr);
	err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	err = pthread_mutex_init(&attr);
	pthread_mutex_lock(&mutex);

	if (condition){
		timeout(&when, retry, (void *)arg);
	}/*condition*/

	pthread_mutex_unlock(&mutex);
	exit(0);
}/*main:returns:*/
