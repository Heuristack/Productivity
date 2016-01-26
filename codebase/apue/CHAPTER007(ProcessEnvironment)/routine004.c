/**
 * Subject: Environment List
 * Author: LiYing
 */

/**
 * Environment List
 * environment pointer: extern char **environ; (global variable)
 * environment list:    array of pointer to strings (array of char)
 * environment strings: array of char with "name=value"
 */
/**
 * Environment Processing Loop
 * for (i = 0; environ[i] != NULL; i++)
 * for (p = environ; *p != NULL; p++)
 */

#include<stdio.h>
#include<stdlib.h>
extern char **environ;

int main(){
	int i;
	char **p;

	for (i = 0; environ[i] != NULL; i++)
		printf("Environment String[%d]: %s\n", i, environ[i]);
	for (p = environ; *p != NULL; p++)
		printf("Environment String[%d]: %s\n", (p-environ), *p);

	setenv("liying", "hello", 1);
	printf("main:environment-string:%s\n", getenv("liying"));
	exit(0);
}/*main*/
