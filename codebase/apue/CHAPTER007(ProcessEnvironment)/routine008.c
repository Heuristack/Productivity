/**
 * Subject: Environment Strings
 * Author: LiYing
 */

/**
 * FUNCTION PROTOTYPE
 * #include<stdlib.h>
 * char *getenv(const char *name);
 * 			Returns:pointer to value associated with name, NULL if not found.
 * int putenv(char *str);
 * int setenv(const char *name, const char *value, int rewrite);
 * int unsetenv(const char *name);
 * int clearenv();
 */
/**
 * #include<stdlib.h>
 * int putenv(char *str);
 * usage: putenv("name=value");
 * If name already exists, its ole definition is first removed.
 */
/**
 * #include<stdlib.h>
 * int setenv(const char *name, const char *value, int rewrite);
 * usage: setenv("name", "value", rewrite);
 * If name already exists, then
 * (a) if rewrite is non-zero, replace
 * (b) if rewrite is zero, do nothing
 * Not supported on HP-UX
 */
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	printf("%s\n", getenv("HOME"));
	putenv("LIYING=lance");
	printf("%s\n", getenv("LIYING"));
	setenv("LIYING", "lancelee", 0);
	printf("%s\n", getenv("LIYING"));
	setenv("LIYING", "lancelee", 1);
	printf("%s\n", getenv("LIYING"));
}/*main*/
