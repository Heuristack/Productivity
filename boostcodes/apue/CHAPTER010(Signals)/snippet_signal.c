
//signal function
#include<signal.h>
void (*signal(int signo, void (*func)(int)))(int);
//returns: previous disposition of signal if OK, SIG_ERR on	error

//kill and raise function
int kill(pid_t pid, int signo);
int raise(int signo);
//returns: zero if OK, -1 on error


//alarm and pause function
#include<unistd.h>
unsigned int alarm(unsigned int seconds);
//returns: zero or number of seconds until previously set alarm

int pause(void);
//returns: -1 on error with errno set to EINTR

//sigset operation functions
int sigfillset(sigset_t *set);
int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);
int sigdelset(sigset_t *set, int signo);
//returns: zero if OK, -1 on error
int sigismember(const sigset_t *set, int signo);
//returns: one if true, zero if false, -1 on error

//sigprocmask function
int sigprocmask(int how, const sigset_t *set, sigset_t *oset);
//returns: zero if OK, -1 on error

//sigpending function
int sigpending(sigset_t *set);
//returns: zero if OK, -1 on error

//sigsetjmp and siglongjmp functions
#include<setjmp.h>
int sigsetjmp(sigjmpbuf env, int savemask);
//returns: zero if called directly, nonzero if returning from a call to siglongjmp
void siglongjmp(sigjmpbuf env, int val);

//sigsuspend function
#include<signal.h>
int sigsuspend(const sigset_t *sigmask);
//returns: -1 with errno set to EINTR

//sigaction function
#include<signal.h>
int sigaction(int signo, struct sigaction *act, sturct sigaction *oact);
//returns: zero if OK, -1 on error

//signal generation: event->signal
//signal delivery: signal->handler
//signal pending: state between generation and delivery

//signal sending: kill; raise; alarm; abort;
//signal waiting(blocking process to wait not busy-waiting): pause; sigsuspend; sigwait;
//signal handling: sigaction; signal; handlers;
//signal blocking: sigprocmask;
//signal set operations: sigemptyset; sigfillset; sigaddset; sigdelset; sigismember;
//signal pending checks: sigpending;

//signal control flow: sigsetjmp; siglongjmp;

//real-time-extentions: application defined signals
