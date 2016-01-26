/**
 * SUBJECT: Sessions
 * AUTHOR: LiYing
 */
/**
 * SESSIONS -- a collection of one or more process groups
 *
 */
/**
 * FUNCTION PROTOTYPE -- establishes a new session
 * #include<unistd.h>
 * pid_t setsid(void);
 * returns: process group id if OK, one on error
 */
/**
 * SETSID -- CREATE A NEW SESSION
 * creating a new session (if calling process is not the group leader)
 * 1.The process becomes the session leader of this new session.(A session leader is the process that creates a session.)
 *   The process is the only process in this new session.
 * 2.The process becomes the process group leader of a new process group.
 *   The new process group ID is the process ID of the calling process.
 * 3.The process has no controlling terminal.
 *   If the process had a controlling terminal before calling setsid, that association is broken.
 * This function returns an error if the caller is already a process group leader.
 */
/**
 * ENSUREMENT SKILL -- FORK && TERMINATE PARENT
 * To ensure this is not the case, the usual practice is to call fork and have the parent terminate and the child continue.
 * We are guaranteed that the child is not a process group leader, because the process group ID of the parent is inherited by the child,
 * but the child gets a new process ID. Hence, it is impossible for the child's process ID to equal its inherited process group ID.
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * pid_t getsid(pid_t pid);
 * returns: session leader's process group id if OK, minus one on error
 */
#include<stdio.h>
#include<unistd.h>

int main(){
	printf("session id is %d\n", getsid(0));
}/*main*/
