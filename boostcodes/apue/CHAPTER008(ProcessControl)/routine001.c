/**
 * SUBJECT: Process Identifiers
 * AUTHOR: LiYing
 */
/**
 * PROCESS IDENTIFIERS
 *
 */
/**
 * FUNCTION PROTOTYPES
 * #include<unistd.h>
 * pid_t getpid(void);		returns: process id of the calling process
 * pid_t getppid(void);		returns: parent process id of the calling process
 * uid_t getuid(void);		returns: real user id of the calling process
 * uid_t geteuid(void);		returns: effictive user id of the calling process
 * gid_t getgid(void);		returns: real group id of the calling process
 * gid_t getegid(void);		returns: effictive group id of the calling process
 * Note: no error returns
 */

#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	printf("Process id: %d\n", (int)getpid());
	printf("Parent id: %d\n", (int)getppid());
	printf("Real user id: %d\n", (int)getuid());
	printf("Effictive user id: %d\n", (int)geteuid());
	printf("Real group id: %d\n", (int)getgid());
	printf("Effictive group id: %d\n", (int)getegid());
}/*main*/
