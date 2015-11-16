/**
 * TITLE: stringizing operator(#) and concatenation operator (##)
 * AUTHOR: LiYing
 * DATE: 2010-5-19 9:33:47
 * NOTE: 1.#v make macro parameter v converted to "v";
 */
#include<stdio.h>
#include<signal.h>

#define DEBUG_VALUE(v) printf(#v"\n");
#define SORT(x) sort_function##x

int sort_function1(char *s, int e, int e_size){
	printf("sort_function1: \n");
}/*sort_function1*/

int sort_function2(char *s, int e, int e_size){
	printf("sort_function2: \n");
}/*sort_function2*/

int sort_function3(char *s, int e, int e_size){
	printf("sort_function3: \n");
}/*sort_function3*/

int main(int argc, char *argv[]){
	char s[] = "hello";
	int e, e_size;
	int i = 4;
	DEBUG_VALUE(SIG_ERR);
	DEBUG_VALUE(SIGKILL);
	DEBUG_VALUE(123);
	SORT(1)(s, e, e_size);
	SORT(3)(s, e, e_size);
	SORT(2)(s, e, e_size);
/*	SORT(i/2)(s, e, e_size);*/
/*  cannot pass the compiler: "routine030.c", line 35.9: 1506-045 (S) Undeclared identifier sort_functioni*/
}/*main*/
