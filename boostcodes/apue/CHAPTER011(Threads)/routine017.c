/**
 * TITLE: A thread-safe, compatible version of getenv
 * AUTHOR: LiYing
 * DATE: 2010-9-10 10:48:35
 * NOTE:
 */

#include<pthread.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void thread_init(void){
	pthread_key_create(&key, free);
}/*thread_init:returns:void*/

char *getenv(const char *name){
	int		i, len;
	char	*envbuf;

	pthread_once(&init_done, thread_init);

	pthread_mutex_lock(&env_mutex);

	envbuf = (char *)pthread_getspecific(key);
	if (envbuf == NULL){
		envbuf = malloc(ARG_MAX);
		if (envbuf == NULL){
			pthread_mutex_unlock(&env_mutex);
			return (NULL);
		}/*no-heap*/
		pthread_setspecific(key, envbuf);
	}/*key-available*/

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++;){
		if (strncmp(name, environ[i], len)==0 && environ[i][len] == '='){
			strcpy(envbuf, &environ[i][len+1]);		//get the string
			pthread_mutex_unlock(&env_mutex);
			return (envbuf);
		}/*found*/
	}/*traverse-environ*/

	pthread_mutex_unlock(&env_mutex);
	return (NULL);
}/*getenv:returns:void*/
