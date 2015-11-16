/**
 * Subject: Process Termination -- exit status
 * Author: LiYing
**/

/**
 * Eight ways for a process to terminate, Normal or Abnormal
 * TW01(N): return from main
 * TW02(N): call exit
 * TW03(N): call _exit or _Exit
 * TW04(N): return of the last thread from its start routine (thread)
 * TW05(N): call pthread_exit from the last thread (thread)
 * TW06(A): call abort
 * TW07(A): receipt of a signal
 * TW08(A): response of the last thread to cancellation request (thread)
**/

/**
 * EXIT FUNCTIONS
 * NAMES	HEADERS			PROTOTYPES					DESCRIPTIONS
 * exit		<stdlib.h>		void exit(int status);		cleanup and return to the kernel
 * _Exit	<stdlib.h>		void _Exit(int status);		return to the kernel immediately
 * _exit	<unistd.h>		void _exit(int status);		return to the kernel immediately
**/
/**
 * EXIT STATUS UNDEFINED
 * Three ways the exit status of a process is undefined
 * UNDEF01: any of these functions is called without an exit status
 * UNDEF02: main does a return without a return value
 * UNDEF03: the main function is not declared to return an integer
**/
#include<stdio.h>

int main(int argc, char *argv[]){
	printf("hello world\n");
}/*main*/
