/**
 * SUBJECT: Process Groups
 * AUTHOR: LiYing
 */
/**
 * PROCESS GROUPS
 * 1.each process also belongs to a process group;
 * 2.a process group is a collection of one or more processes;
 * 3.usually associated with the same job;
 * 4.that can receive signals from the same terminal;
 * 5.each process group can have a process group leader;
 * 6.leader is identified by its process group ID being equal to its process ID;
 */
/**
 * PROCESS GROUP ID
 * 1.Each process belongs to a process group
 * 2.Each process group has a unique process group ID
 * 3.Positive integers and can be stored in a pid_t data type
 * 4.Process group id is the process id of the leader process of the group
 */
/**
 * PROCESS GROUP LEADER
 * 1.It is possible for a process group leader to create a process group
 * 2.create processes in the group
 * 3.terminate
 */
/**
 * PROCESS GROUP LIFETIME
 * 1.The process group still exists, as long as at least one process is in the group, regardless of whether the group leader terminates;
 * 2.The period of time that begins when the group is created and ends when the last remaining process leaves the group;
 * 3.The last remaining process in the process group can either terminate or enter some other process group.
 */
/**
 * PROCESS GROUP CREATION AND JOINING IN
 * 1.A process joins an existing process group or
 * 2.creates a new process group by calling setpgid.
 */
/**
 * FUNCTION PROTOTYPE -- GETPGRP
 * #include<unistd.h>
 * pid_t getpgrp(void);
 * returns: process group id of the calling process
 */
/**
 * FUNCTION PROTOTYPE -- Process Group
 * #include<unistd.h>
 * pid_t getpgid(void);
 * returns: process group id if OK, minus one on error
 */
/**
 * FUNCTION PROTOTYPE -- SETPGID
 * #include<unistd.h>
 * int setpgid(pid_t pid, pid_t pgid);
 * returns: zero if OK, minus one on error
 */
/**
 * ARGUMENTS AND MEANING OF PGID
 * 1.pid != pgid: pgid of the group where pid process in is set to pgid;
 * 2.pgid = pid:  pid process becomes the group leader of the former process group pid in;
 * 3.pid  = 0: pid is the calling process;
 * 4.pgid = 0: the process id of pid process is used as the process group id;
 */
/**
 * RESTRICTIONS OF SETPGID
 * 1.A process can set the process group ID of only itself or any of its children;
 * 2.Furthermore, it can't change the process group ID of one of its children after that child has called one of the exec functions;
 */
/**
 * ADDITIONAL INFO
 * 1.signals: how to send a signal to either a single process (identified by its process ID) or a process group (identified by its process group ID);
 * 2.waitpid: wait for either a single process or one process from a specified process group;
 */

#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	printf("group id is %d\n", getpgid(0));
	printf("group id is %d\n", getpgrp());
}/*main*/
