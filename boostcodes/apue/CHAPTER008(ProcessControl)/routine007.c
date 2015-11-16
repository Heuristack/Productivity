/**
 * SUBJECT: Process Termination - 'wait' functions
 * AUTHOR: LiYing
 * TIME: 2009-10-22 13:22:05
 */
/**
 * FUNCTION PROTOTYPE -- wait for child process to change state
 * #include<sys/time.h>
 * #include<sys/wait.h>
 * #include<sys/types.h>
 * #include<sys/resource.h>
 * pid_t wait3(int *statloc, int options, struct rusage *rusage);
 * pid_t wait4(pid_t pid, int *statloc, int options, struct rusage *rusage);
 * returns: process id if OK, 0 or 1 on error
 */
/**
 * resource information
 * 1.amount of user cpu time
 * 2.amount of system cpu time
 * 3.number of page faults
 * 4.number of signals received
 */

#include<stdio.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/resources.h>

int main(int argc, char **argv){}/*main*/
