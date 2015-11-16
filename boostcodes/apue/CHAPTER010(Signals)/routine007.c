/**
 * TITLE: alarm and pause functions
 * AUTHOR: LiYing
 * DATE: 2010-5-14 17:35:50
 * NOTE:
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * unsigned int alarm(unsigned int seconds);
 * returns: zero or number of seconds until previously set alarm
 */
/**
 * ALARM DESCRIPTION -- SIGALRM
 * The alarm function allows us to set a timer that will expire at a specified time in the future.
 * When the timer expires, the SIGALRM signal is generated.
 * If we ignore or don't catch this signal, its default action is to terminate the process.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

static void test_case01(void);
static void test_case02(void);
static void test_case03(void);

int main(){
	test_case03();
	exit(0);
}/*main*/

static void test_case01(void){
	int ret;
	int seconds = 5;

	printf("before alarm\n");
	ret = alarm(seconds);
	pause();
	printf("after alarm\n");
	exit(0);
}/*test_case01*/

static void test_case02(void){
	int ret;
	int seconds = 2;

	printf("before alarm\n");
	ret = alarm(seconds);
	while(1)
		;
	printf("after alarm\n");
	exit(0);
}/*test_case02*/

static void signal_handler(int signo){
	printf("signal_handler: really do nothing ");
	printf("but just exit\n");
	exit(1);
}/*signal_handler*/

static void test_case03(void){
	int ret;

	signal(SIGALRM, signal_handler);
	printf("before alarm\n");
	ret = alarm(5);
	sleep(1);
	ret = alarm(3);
	printf("return value of alarm is %d\n", ret);
	while(1)
		;
	printf("after alarm\n");
	exit(0);
}/*test_case03*/
