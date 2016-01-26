/**
 * TITLE: Using a mutex to protect a data structure
 * AUTHOR: LiYing
 * DATE: 2010-9-6 10:34:43
 * NOTE:
 */

#include<pthread.h>
#include<stdlib.h>

struct foo {
	int				f_conut;
	pthread_mutex_t	f_lock;
};

struct foo *foo_alloc(void){	//allocate the object
	struct foo *fp;

	if ((fp = malloc(sizeof(struct foo))) != NULL){
		fp->f_count = 1;
		if (pthread_mutex_init(&foo->f_lock, NULL) != 0){
			free(fp);
			return NULL;
		}/*init mutex*/
	}/**/
	return (fp);
}/*foo_alloc:returns:pointer to foo object*/

void foo_hold(struct foo *fp){
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}/*foo_hold:returns:void*/

void foo_rele(struct foo *fp){
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0){
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destory(&fp->f_lock);
		free(fp);
	}/**/
	else {
		pthread_mutex_unlock(&fp->f_lock);
	}/**/
}/*foo_rele:returns:void*/

int main(int argc, char *argv[]){
	exit(0);
}/*main*/
