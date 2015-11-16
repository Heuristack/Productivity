/**
 * TITLE: A nonreentrant version of getenv
 * AUTHOR: LiYing
 * DATE: 2010-9-10 10:47:54
 * NOTE:
 */

#include<string.h>
#include<limits.h>

static char envbuf[ARG_MAX];

extern char **environ;

char *getenv(const char *name){
	int i, len;
	len = strlen(name);

	for (i = 0; environ[i] != NULL; i++ ){
		if ((strncmp(name, environ[i]) == 0) &&
			(environ[i][len] == '=')){
			strncpy(envbuf, &environ[i][len+1]);
			return (envbuf)
		}/**/
	}/*traverse the environment-lis*/
	return (NULL);
}/*getenv:returns:*/

