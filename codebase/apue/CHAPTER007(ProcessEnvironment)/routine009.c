/**
 * Subject: Nonlocal Goto
 * Author: LiYing
 */

/**
 * FUNCTION PROTOTYPE
 * #include<setjmp.h>
 * int setjmp(jmp_buf env);
 * void longjmp(jmp_buf env, int val);
 */
/**
 * BRANCHING: GO TO A LABEL IN ANOTHER FUNCTION
 * Handling error conditions occur in deeply nested function call
 * Hardware support for stacks | Linked List Implemention
 */
/**
 * AUTOMATIC, REGISTER AND VOLATILE VARIABLES
 *
 */
/**
 * GLOBAL MEMORY ALLOCATION
 * Static:  static | extern
 * Dynamic: 'alloc'function
 */
#include<setjmp.h>
#include<stdio.h>

static jmp_buf jmpbuffer;
static int global_val;

static void f1(int, int, int, int);
static void f2(void);

int main(int argc, char *argv[]){
	auto int automatic_val;
	register int register_val;
	volatile int volatile_val;
	static   int static_val;

	global_val = 1; automatic_val = 2; register_val = 3; volatile_val = 4; static_val = 5;

	if (setjmp(jmpbuffer) != 0){
		printf("after longjmp: \n");
		printf("global = %d, auto = %d, register = %d, volatile = %d, static = %d\n",
				global_val, automatic_val, register_val, volatile_val, static_val);
		exit(0);
	}/*jmp point*/
	global_val = 91; automatic_val = 92; register_val = 93; volatile_val = 94; static_val = 95;

	f1(automatic_val, register_val, volatile_val, static_val);
	exit(0);
}/*main*/

static void f1(int i, int j, int k, int l){
	printf("in f1(): \n");
	printf("global = %d, auto = %d, register = %d, volatile = %d, static = %d\n",
			global_val, i, j, k, l);
	f2();
}/*f1*/

static void f2(void){
	longjmp(jmpbuffer, 1);
}/*f2*/
