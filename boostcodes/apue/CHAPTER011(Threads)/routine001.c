/**
 * TITLE: simple example program that uses POSIX threads
 * AUTHOR: LiYing
 * DATE: 2010-5-24 19:48:18
 * NOTE: http://www.ibm.com/developerworks/library/l-posix1.html
 */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *arg) {
  int i;
  for ( i=0; i<20; i++ ) {
    printf("Thread[%d] says hi!\n", pthread_self());
    sleep(1);
  }
  return NULL;
}

int main(void) {

  pthread_t thread1;
  pthread_t thread2;

  if ( pthread_create( &thread1, NULL, thread_function, NULL) ) {
    printf("error creating thread.");
    abort();
  }

  if ( pthread_create( &thread2, NULL, thread_function, NULL) ) {
    printf("error creating thread.");
    abort();
  }

  if ( pthread_join ( thread1, NULL ) ) {
    printf("error joining thread.");
    abort();
  }

  if ( pthread_join ( thread2, NULL ) ) {
    printf("error joining thread.");
    abort();
  }

  exit(0);
}/*main*/

