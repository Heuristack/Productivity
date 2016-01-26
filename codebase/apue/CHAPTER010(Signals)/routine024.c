/**
 * TITLE: An implementation of sigaddset, sigdelset, and sigismember
 * AUTHOR: LiYing
 * DATE: 2010-5-17 16:05:31
 * NOTE: How to deal with type conversions?
 */
#include<signal.h>
#include<errno.h>

#define SIGBAD(signo)	((signo) <=0 || (signo) >= NSIG)

int sigaddset(sigset_t *set, int signo){
	if (SIGBAD(signo)) { errno = EINVAL; return (-1);}/*SIGBAD*/
	*set |= 1 << (signo - 1);
	return 0;
}/*sigaddset*/

int sigdelset(sigset_t *set, int signo){
	if (SIGBAD(signo)) { errno = EINVAL; return (-1);}/*SIGBAD*/
	*set &= ~(1 << (signo - 1));
	return 0;
}/*sigdelset*/

int sigismember(const sigset_t *set, int signo){
	if (SIGBAD(signo)) { errno = EINVAL; return (-1);}/*SIGBAD*/
	return ((*set & (1 << (signo -1))) != 0 );
}/*sigismember*/

int main(int argc, char *argv[]){

}/*main*/
