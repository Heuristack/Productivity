/**
 * TITLE: Using readerwriter locks
 * AUTHOR: LiYing
 * DATE: 2010-9-6 20:44:52
 * NOTE:
 */

#include<pthread.h>
#include<stdlib.h>

struct job {
	struct job *j_next;
	struct job *j_prev;
	pthread_t	j_id;
};

struct queue {
	struct job 		*q_head;
	struct job 		*q_tail;
	pthread_rwlock_t q_lock;
};

int queue_init(struct queue *qp){
	int err;

	qp->q_head = NULL;
	qp->q_tail = NULL;
	err = pthread_rwlock_init(&qp->q_lock, NULL);
	if (err != 0)
		return (err);
	return (0);
}/*queue_init:returns:1.OK:zero;2.err:negative*/

void job_insert(struct queue *qp, struct job *jp){
	pthread_rwlock_wrlock(&qp->q_lock);
	jp->next = qp->head;
	jp->prev = NULL;
	if (qp->head != NULL)
		qp->head->prev = jp;
	else
		qp->q_tail = jp;
	qp->head = jp;
	pthread_rwlock_unlock(&qp->q_lock);
}/*job_insert:returns:void*/

void job_append(struct queue *qp, struct job *jp){
	pthread_rwlock_wrlock(&qp->q_lock);

	jp->next = NULL
	jp->prev = qp->tail;
	if (qp->tail != NULL)
		qp->tail->next = jp;
	else
		qp->head = jp;
	qp->q_tail = jp;
	pthread_rwlock_unlock(&qp->q_lock);
}/*job_append:returns:void*/


void job_remove(struct queue *qp, struct job *jp){
	pthread_rwlock_wrlock(&qp->q_lock);
	if (jp == qp->head){
		qp->head = jp->next;
		qp->head->prev = NULL;
		if (qp->tail == jp)
			qp->tail = NULL;
	}/*head*/
	else if (jp == qp->tail){
		qp->tail = jp->prev;
		qp->tail->next = NULL;
		if (qp->head == jp)
			qp->head = NULL;
	}/*tail*/
	else {
		jp->prev->next = jp->next;
		jp->next->prev = jp->prev;
	}/*middle*/
	pthread_rwlock_unlock(&qp->q_lock);
}/*job_remove:returns:void*/


struct job *job_find(struct queue *qp, pthread_t id){
	struct job *jp;
	if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
		return NULL;
	for (jp = qp->head; jp != NULL; jp = jp->next;)
		if (pthread_equal(id, jp->j_id))
			break;

	pthread_rwlock_unlock(&qp->q_lock);
	return (jp);
}/*job_find:returns: pointer to job object*/


int main(int argc, char *argv[]){
	exit(0);
}/*main*/
