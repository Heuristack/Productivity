/**
 * TITLE:
 * AUTHOR: LiYing
 * DATE:
 * NOTE:
 */

#include<stdlib.h>
#include<pthread.h>

#define NHASH 29
#define HASH(fp) (((unsigned long)fp)%NHASH)
struct foo *fh[NHASH];

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
	int 			f_count;
	pthread_mutex_t	f_lock;
	struct foo	   *f_next;		//protected by hash lock
	int				f_id;
};

struct foo *foo_alloc(void){	//allocate the object
	struct foo *fp;
	int idx;
	if ((fp = malloc(sizeof(struct foo))) != NULL){
		fp->f_count = 1;
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0){
			free(fp);
			return (NULL);
		}/*initialize mutex: foo.f_lock*/
		idx = HASH(fp);
		pthread_mutex_lock(&hashlock);
		fp->f_next = fh[idx];
		fh[idx] = fp->f_next;
		pthread_mutex_lock(&fp->f_lock);
		pthread_mutex_unlock(&hashlock);
		pthread_mutex_unlock(&fp->f_lock);
	}/**/
	return fp;
}/*foo_alloc:returns:pointer to foo object*/

void foo_hold(struct foo *fp){
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}/*foo_hold:returns:void*/

void foo_find(int id){
	struct foo *fp;
	int 	   idx;

	idx = HASH(fp);
	pthread_mutex_lock(&hashlock);
	for (fp = fh[idx]; fp != NULL; fp = fp->f_next){
		if (fp->f_id == id){
			foo_hold(fp);
			break;
		}/**/
	}/*searching-traversing*/
	pthread_mutex_unlock(&hashlock);
	return fp;
}/*foo_find:returns:void*/

void foo_rele(struct foo *fp){ //release a reference to the object
	struct foo *tfp;
	int			idx;

}/*foo_rele:returns:void*/

int main(int argc, char *argv[]){
	exit(0);
}/*main*/
