/**
 * TITLE: siginfo structure and its si_code memeber (message mapping printing)
 * AUTHOR: LiYing
 * DATE: 2010-5-19 9:59:04
 * NOTE:
 */
#include<signal.h>
#include<stdio.h>

void print_si_code(void);
#define macro_message(macro, message) printf(#macro"(%d): %s\n", (macro), (message))

int main(int argc, char *argv[]){
	print_si_code();
}/*main*/

void print_si_code(void){
	/*SIGILL*/
	macro_message(ILL_ILLOPC, "illegal opcode");
	macro_message(ILL_ILLOPN, "illegal operand");
	macro_message(ILL_ILLADR, "illegal addressing mode");
	macro_message(ILL_ILLTRP, "illegal trap");
	macro_message(ILL_PRVOPC, "privileged opcode");
	macro_message(ILL_PRVREG, "privileged register");
	macro_message(ILL_COPROC, "coprocessor error");
	macro_message(ILL_BADSTK, "internal stack error");

	/*SIGFPE*/
	macro_message(FPE_INTDIV, "integer divide by zero");
	macro_message(FPE_INTOVF, "integer overflow");
	macro_message(FPE_FLTDIV, "floating-point divide by zero");
	macro_message(FPE_FLTOVF, "floating-point overflow");
	macro_message(FPE_FLTUND, "floating-point underflow");
	macro_message(FPE_FLTRES, "floating-point inexact result");
	macro_message(FPE_FLTINV, "invalid floating-point operation");
	macro_message(FPE_FLTSUB, "subscript out of range");

	/*SIGSEGV*/
	macro_message(SEGV_MAPERR, "address not mapped to object");
	macro_message(SEGV_ACCERR, "invalid permissions for mapped object ");

	/*SIGBUS*/
	macro_message(BUS_ADRALN, "invalid address alignment");
	macro_message(BUS_ADRERR, "nonexistent physical address");
	macro_message(BUS_OBJERR, "object-specific hardware error ");

	/*SIGCHLD*/
	macro_message(CLD_EXITED, "child has exited");
	macro_message(CLD_KILLED, "child has terminated abnormally (no core)");
	macro_message(CLD_DUMPED, "child has terminated abnormally with core");
	macro_message(CLD_TRAPPED, "traced child has trapped");
	macro_message(CLD_STOPPED, "child has stopped");
	macro_message(CLD_CONTINUED, "stopped child has continued ");

	/*SIGPOLL*/
	macro_message(POLL_IN,  "data can be read");
	macro_message(POLL_OUT, "data can be written");
	macro_message(POLL_MSG, "input message available");
	macro_message(POLL_ERR, "I/O error");
	macro_message(POLL_PRI, "high-priority message available");
	macro_message(POLL_HUP, "device disconnected");

	/*ANY*/
	macro_message(SI_USER, "signal sent by kill");
	macro_message(SI_QUEUE, "signal sent by sigqueue (real-time extension)");
	macro_message(SI_TIMER, "expiration of a timer set by timer_settime (real-time extension)");
	macro_message(SI_ASYNCIO, "completion of asynchronous I/O request (real-time extension)");
	macro_message(SI_MESGQ, "arrival of a message on a message queue (real-time extension)");

}/*print_si_code*/
