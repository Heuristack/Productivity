/**
 * SUBJECT: SHARED MEMORY
 * AUTHOR: LIYING
 */
/**
 * SHMGET -- GET SHARED MEMORY SEGMENT
 * #include<sys/shm.h>
 * int shmget(key_t key, size_t size, int shmflag);
 * returns: shared memory id if OK, minus one on error
 */
/**
 * SHMCTL -- SHARED MEMORY CONTROL OPERATINOS
 * #include<sys/shm.h>
 * int shmctl(int shmid, int cmd, struct shmid_ds *buf);
 * returns: zero if OK, minus one on error
 */
/**
 * SHMAT -- ATTACH SHARED MEMORY TO CALLING PROCESS
 * #include<sys/shm.h>
 * void *shmat(int shmid, void * shmaddr, int shmflag);
 * returns: pointer to shared memory segment if OK, minus one on error
 */
/**
 * SHMDT -- DETACH SHARED MEMORY FROM CALLING PROCESS
 * #include<sys/shm.h>
 * int shmdt(void *addr);
 * returns: zero on OK, minus one on error
 */
/**
 * KERNEL DATA STRCUTURE
 * struct shmid_ds {
 * 	struct ipc_perm	shm_perm;
 *	size_t 			shm_segsz;
 *	pid_t			shm_lpid;
 *	pid_t			shm_cpid;
 *	shmatt_t		shm_nattch;
 * 	time_t			shm_atime;
 *	time_t			shm_dtime;
 * 	time_t			shm_ctime;
 *	...
 * };
 */
/**
 * COMMANDS FOR SHMCTL
 * IPC_STAT:  1.fetch shmid_ds structure for this segment,storing it in structure pointed by buf
 * IPC_SET:   2.Set the following three fields from the structure pointed to by buf in the shmid_ds structure associated with this shared memory segment: shm_perm.uid, shm_perm.gid, and shm_perm.mode.
 * IPC_RMID:  3.Remove the shared memory identifier specified by shmid from the system and destroy the shared memory segment and data structure associated with it.
 * IPC_LOCK:  4.Lock the shared memory segment specified by shmid in memory.
 * IPC_UNLOCK:5.Unlock the shared memory segment specified by shmid.
 */
/**
 * EXAMPLE1:
 * int myshmid;
 * myshmid = shmget(IPC_PRIVATE, 4096, 0600);
 * EXAMPLE2:
 * char *shmptr;
 * shmptr = (char *)shmat(myshmid, 0, 0);
 * shmdt(shmptr);
 * EXAMPLE3:
 * shmctl(myshmid, IPC_RMID, 0);
 * shmctl(myshmid, SHM_LOCK, 0);
 * shmctl(myshmid, SHM_UNLOCK, 0);
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>

#define ARRAY_SIZE 	40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 	100000
#define SHM_MODE 	0600

char array[ARRAY_SIZE];

int main(){
	int shmid;
	char *ptr, *shmptr;

	printf("array from %lx to %lx\n", (unsigned long)&array[0], (unsigned long)&array[ARRAY_SIZE]);
	printf("stack around %lx\n", (unsigned long)&shmid);

	if ((ptr = malloc(MALLOC_SIZE)) != NULL){
		printf("malloc from %lx to %lx\n", (unsigned long)ptr, (unsigned long)ptr+MALLOC_SIZE);
	}/*malloc*/

	shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE);
	shmptr = shmat(shmid, 0, 0);
	printf("shared memory attached from %lx to %lx\n", (unsigned long)shmptr, (unsigned long)shmptr+SHM_SIZE);

	shmctl(shmid, IPC_RMID, 0);
	exit(0);
}/*main*/
