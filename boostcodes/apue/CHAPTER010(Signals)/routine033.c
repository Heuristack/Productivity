/**
 * TITLE: sigaction structure, sigaction function, sa_sigaction handler pointer
 * AUTHOR: LiYing
 * DATE: 2010-5-21 19:59:14
 * NOTE:
 */

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>

typedef struct sigaction sigaction_t;

typedef void (* sa_sigaction_t)(int, siginfo_t *, void *);

siginfo_t *p_signal_info;

#define END_SIGNO 0xffff

typedef struct siginfo_code {
	int no;					/*sicode signal number*/
	char *name;				/*sicode name*/
	char *message;			/*sicode message*/
} siginfo_code_t;

siginfo_code_t sicode_message[] = {
	ILL_ILLOPC, "ILL_ILLOPC", "illegal opcode",
	ILL_ILLOPN, "ILL_ILLOPN", "illegal operand",
	ILL_ILLOPC, "ILL_ILLOPC", "illegal opcode",
	ILL_ILLOPN, "ILL_ILLOPN", "illegal operand",
	ILL_ILLADR, "ILL_ILLADR", "illegal addressing mode",
	ILL_ILLTRP, "ILL_ILLTRP", "illegal trap",
	ILL_PRVOPC, "ILL_PRVOPC", "privileged opcode",
	ILL_PRVREG, "ILL_PRVREG", "privileged register",
	ILL_COPROC, "ILL_COPROC", "coprocessor error",
	ILL_BADSTK, "ILL_BADSTK", "internal stack error",
	FPE_INTDIV, "FPE_INTDIV", "integer divide by zero",
	FPE_INTOVF, "FPE_INTOVF", "integer overflow",
	FPE_FLTDIV, "FPE_FLTDIV", "floating-point divide by zero",
	FPE_FLTOVF, "FPE_FLTOVF", "floating-point overflow",
	FPE_FLTUND, "FPE_FLTUND", "floating-point underflow",
	FPE_FLTRES, "FPE_FLTRES", "floating-point inexact result",
	FPE_FLTINV, "FPE_FLTINV", "invalid floating-point operation",
	FPE_FLTSUB, "FPE_FLTSUB", "subscript out of range",
	BUS_ADRALN, "BUS_ADRALN", "invalid address alignment",
	BUS_ADRERR, "BUS_ADRERR", "nonexistent physical address",
	BUS_OBJERR, "BUS_OBJERR", "object-specific hardware error ",
	CLD_CONTINUED, "CLD_CONTINUED", "stopped child has continued ",
	CLD_EXITED, "CLD_EXITED", "child has exited",
	CLD_KILLED, "CLD_KILLED", "child has terminated abnormally (no core)",
	CLD_DUMPED, "CLD_DUMPED", "child has terminated abnormally with core",
	CLD_TRAPPED, "CLD_TRAPPED", "traced child has trapped",
	CLD_STOPPED, "CLD_STOPPED", "child has stopped",
	SEGV_MAPERR, "SEGV_MAPERR", "address not mapped to object",
	SEGV_ACCERR, "SEGV_ACCERR", "invalid permissions for mapped object ",
	POLL_IN,  "POLL_IN",  "data can be read",
	POLL_OUT, "POLL_OUT", "data can be written",
	POLL_MSG, "POLL_MSG", "input message available",
	POLL_ERR, "POLL_ERR", "I/O error",
	POLL_PRI, "POLL_PRI", "high-priority message available",
	POLL_HUP, "POLL_HUP", "device disconnected",
	SI_USER,  "SI_USER",  "signal sent by kill",
	SI_QUEUE, "SI_QUEUE", "signal sent by sigqueue (real-time extension)",
	SI_TIMER, "SI_TIMER", "expiration of a timer set by timer_settime (real-time extension)",
	SI_MESGQ, "SI_MESGQ", "arrival of a message on a message queue (real-time extension)",
	SI_ASYNCIO, "SI_ASYNCIO", "completion of asynchronous I/O request (real-time extension)",
	END_SIGNO,	NULL , NULL
};

char *str_sicode(int signo){
	static char str_sicode[0xf];
	memset(str_sicode, 0, sizeof(str_sicode));
	siginfo_code_t *s = sicode_message;
	while (s->name != NULL) {
		if (s->no == signo) {
			strcpy(str_sicode, s->name);
			break;
		} /*test*/
		s++;
	} /*searching-traverse*/
	return str_sicode;
}/*strsicode*/

char *message_sicode(int signo){
	static char str_sicode[0xff];
	memset(str_sicode, 0, sizeof(str_sicode));
	siginfo_code_t *s = sicode_message;
	while (s->name != NULL) {
		if (s->no == signo) {
			strcpy(str_sicode, s->message);
			break;
		} /*test*/
		s++;
	} /*searching-traverse*/
	return str_sicode;
}/*message_sicode*/

void print_siginfo(siginfo_t *psi){
	printf("pinrt_siginfo: si_signo = %d\n", psi->si_signo);
	printf("pinrt_siginfo: si_errno = %d\n", psi->si_errno);
	printf("pinrt_siginfo: si_code = %d\n", psi->si_code);
	printf("pinrt_siginfo: si_pid = %d\n", psi->si_pid);
	printf("pinrt_siginfo: si_uid = %d\n", psi->si_uid);
	printf("pinrt_siginfo: si_addr = %d\n", psi->si_addr);
	printf("pinrt_siginfo: si_status = %d\n", psi->si_status);
	printf("pinrt_siginfo: si_band = %ld\n", psi->si_band);

	printf("pinrt_siginfo: si_code = %d\n", psi->si_code);
	printf("pinrt_siginfo: si_code name: %s\n", str_sicode(psi->si_code));
	printf("pinrt_siginfo: si_code message: %s\n", message_sicode(psi->si_code));
}/*pinrt_siginfo*/

void handler(int signo, siginfo_t *psi, void *buffer){
	printf("handler: received signo = %d\n", signo);
	printf("handler: received context %s\n", buffer);
	print_siginfo(psi);
}/*handler*/

int main(int argc, char *argv[]){
	struct sigaction sa;
	struct sigaction osa;

	int r = 0;
	sa.sa_handler = NULL;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGHUP);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	r = sigaction(SIGINT, &sa, &osa);
	if (r < 0) {
		perror("main: sigaction failed");
		exit(1);
	}/*sigaction-failed*/
	raise(SIGINT);
}/*main*/

