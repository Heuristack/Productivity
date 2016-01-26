/**
 * SUBJECT: alarm and pause functions
 * AUTHOR: LiYing
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * int pause(void);
 * returns: minus one with errno set to EINTR
 */
/**
 * PAUSE DESCRIPTION --
 * The pause function suspends the calling process until a signal is caught.
 * The only time pause returns is if a signal handler is executed and that handler returns.
 * In that case, pause returns -1 with errno set to EINTR.
 */

#include<unistd.h>
#include<string.h>
#include<stdio.h>

extern int errno;

int main(){
	int ret;
	ret = pause();
	printf("reture value of pause%d\n", ret);
	perror("pause: ");
	printf("%s\n", strerror(errno));
}/*main*/
