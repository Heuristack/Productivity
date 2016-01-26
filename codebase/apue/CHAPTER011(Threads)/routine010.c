/**
 * TITLE: Simplified locking
 * AUTHOR: LiYing
 * DATE: 2010-9-6 20:16:24
 * NOTE:
 */

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define NHASH 29
#define HASH(fp) (((unsigned long)fp)%NHASH)

struct foo *fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
	int					f_count;	//protected by hashlock
	pthread_mutex_lock	f_lock;
	struct foo		   *f_next;		//protected by hashlock
	int					f_id;
};

struct foo foo_alloc(void){			//allocate foo object
	struct foo *fp
	int			idx;
	if ((fp = malloc(sizeof(struct foo))) != NULL){
		if ((pthread_mutex_init(&fp->f_lock, NULL)) != 0){
			free(fp);
			return NULL;
		}/**/
		idx = HASH(fp);
		pthread_mutex_lock(&hashlock);
		fp->f_next = fh[idx];
		fh[idx] = f->f_next;
		pthread_mutex_lock(&fp->f_lock);
		pthread_mutex_unlock(&hashlock);
	}/*foo object allocation*/
	return (fp);
}/*foo_alloc: returns: pointer to foo object*/

void foo_hold(sturct foo *fp){
	pthread_mutex_lock(&hashlock);
	fp->f_count++;
	pthread_mutex_unlock(&hashlock);
}/*foo_hold: returns: void*/

struct foo *foo_find(int id){
	struct foo *fp;
	int			idx;

	idx = HASH(fp);
	pthread_mutex_lock(&hashlock);
	for (fp = fh[idx]; fp != NULL, fp = fp->f_next){
		if (fp->f_id == id){
			fp->f_count++;
			break;
		}/*found*/
	}/*foo list traverse*/
	pthread_mutex_unlock(&hashlock);
	return (fp);
}/*foo_find:returns: pointer to foo object*/

void foo_rele(struct foo *fp){
	struct foo *tfp;
	int			idx;

	pthread_mutex_lock(&hashlock);
	if (--fp->f_count == 0){		//last reference, remove from list
		idx = HASH(fp);
		tfp = fh[idx];

		if (tfp == fp) {
			fh[idx] = fp->f_next;
		}/*found directory*/
		else {
			while (tfp->f_next != fp)
			tfp = tfp->f_next;
			tfp->f_next = fp->f_next;
		}/*traverse*/

		pthread_mutex_unlock(&hashlock);
		pthread_mutex_destory(&fp->f_lock);
		free(fp);
	}/*last reference*/
	else {
		pthread_mutex_unlock(&hashlock);
	}/*release mutex hashlock*/
}/*foo_rele: returns: void*/


int main(int argc, char *argv[]){
	exit(0);
}/*main*/
