/**
 * SUBJECT: Job control
 * AUTHOR: LiYing
 */
/**
 * JOB CONTROL
 * This feature allows us
 * to start multiple jobs (groups of processes) from a single terminal and
 * to control which jobs can access the terminal and
 * which jobs are to run in the background.
 */
/**
 * Job control requires three forms of support:
 * SHELL:  1.A shell that supports job control
 * DRIVER: 2.The terminal driver in the kernel must support job control
 * KERNEL: 3.The kernel must support certain job-control signals
 */
/**
 * JOB RECOGNIZATION
 * 1.A job is simply a collection of processes,
 * 2.often a pipeline of processes
 */
/**
 * NOTES:
 * 1.The shell doesn't print the changed status of background jobs at any random time
 * 2.only right before it prints its prompt
 */
/**
 * The terminal driver looks for three special characters, which generate signals to the foreground process group
 * 1.The interrupt character (typically DELETE or Control-C) generates SIGINT
 * 2.The quit character (typically Control-backslash) generates SIGQUIT.
 * 3.The suspend character (typically Control-Z) generates SIGTSTP.
 */
#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){}/*main*/
