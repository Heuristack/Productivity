/**
 * TITLE: sicode_message structure and interface to handle si_code memeber (message mapping structure)
 * AUTHOR: LiYing
 * DATE: 2010-5-19 11:43:16
 * NOTE:
 */

#include<signal.h>
#include<stdio.h>
#include<string.h>

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

int main(int argc, char *argv[]){
	siginfo_code_t *s = sicode_message;

	while (s->name != NULL) {
		printf("%s[%d]: %s\n", s->name, s->no, s->message);
		s++;
	}/*traverse*/

	printf("SI_ASYNCIO: %s\n", str_sicode(SI_ASYNCIO));
	printf("SI_ASYNCIO: %s\n", message_sicode(SI_ASYNCIO));
}/*main*/

