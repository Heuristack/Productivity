/**
 * Subject: Process Termination -- exit handlers
 * Author: LiYing
 */

/**
 * EXIT HANDLERS
 * A process can register up to 32 functions that are automatically called by exit.
 * These are called exit handlers and are registered by calling the atexit function.
 * #include<stdlib.h>
 * 		int atexit(void (*func)(void));
 * Returns: 0 if OK, nonzero on error
 */
/**
 * void kernel(void){
 *     exec((startup_routine)(void));
 * }
 * void startup_routine(void){
 *     main();
 * }
 * main(){
 *     user_function01();
 *     user_function02();
 *     user_function03();
 *     exit(); or
 *     _exit(); or
 *     _Exit();
 * }
 * void user_function01(){
 *     _exit();
 * }
 * void user_function02(){
 *     _Exit();
 * }
 * void user_function03(){
 *     exit();
 * }
 * void _exit(){
 *     return to the kernel;
 * }
 * void _Exit(){
 *     return to the kernel;
 * }
 * void exit(){
 *     exit_handler01();
 *     exit_handler02();
 *     standardIO_cleanup();
 *     _exit();
 *     or
 *     _Exit();
 * }
 */
/**
 * Note:
 * Kernel->Process: exec (only way)
 * Process->Kernel: _exit | _Exit | exit (voluntarily)
 * Process->Kernel: signal (involuntarily)
 */

#include<stdio.h>
#include<stdlib.h>

static void exit_handler1(void);
static void exit_handler2(void);

int main(void){
	if (atexit(exit_handler2) == 0)
		printf("Register Exit Handler No2 Successed.\n");
	if (atexit(exit_handler1) == 0)
		printf("Register Exit Handler No1 Successed.\n");
	if (atexit(exit_handler1) == 0)
		printf("Register Exit Handler No1 Successed.\n");
	printf("Main is done\n");
	exit(1);
}/*main*/

static void exit_handler1(void){
	printf("Exit Handler No1\n");
}/*exit_handler1*/

static void exit_handler2(void){
	printf("Exit Handler No2\n");
}/*exit_handler2*/
