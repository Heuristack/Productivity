/**
 * TITLE: system v semaphores
 * AUTHOR: LiYing
 * DATE: 2010-5-19 16:28:32
 * NOTE:
 */
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdio.h>

#define MutexLock(m) mutex_lock((m))
#define MutexUnLock(m) mutex_lock((m))

union semun{
	int 			 val;
	struct semid_ds *buf;
	unsigned short 	*array;
};
#define IPC_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
#define IPC_PERM 0666

int mutex_init(void){
	union semun su;
	int locker = 0;

	locker = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

	su.val = 1;
	semctl(locker, 0, SETVAL, su);
	return locker;
}/*mutex_init*/

int mutex_lock(int locker){
	struct sembuf sop;
	sop.sem_num = 0;
	sop.sem_op = -1;
	sop.sem_flg = 0;
	return semop(locker, &sop, 1);
}/*mutex_lock*/

int mutex_unlock(int locker){
	struct sembuf sop;
	sop.sem_num = 0;
	sop.sem_op  = 1;
	sop.sem_flg = 0;
	return semop(locker, &sop, 1);
}/*mutex_lock*/

int mutex_destroy(int locker){
	return semctl(locker, 0, IPC_RMID);
}/*mutex_destroy*/

int main(int argc, char *argv[]){
	int locker1;
	int locker2;
	locker1 = mutex_init();
	locker2 = mutex_init();
	printf("locker1=%d\n", locker1);
	printf("locker2=%d\n", locker2);
	mutex_destroy(locker1);
	mutex_destroy(locker2);
}/*main*/
