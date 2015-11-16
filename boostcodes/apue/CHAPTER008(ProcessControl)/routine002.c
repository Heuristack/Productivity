/**
 * SUBJECT: Process Creation -- fork
 * AUTHOR: LiYing
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * 		pid_t fork(void);
 * Returns: 0 in child, process id of child in parent; -1 on error
 */
/**
 * COPY-ON-WRITE (COW)
 *
 */
/**
 * I/O BUFFERING
 *
 */
/**
 * FILE SHARING
 * per-process table entry
 * file table
 * v-node table
 *
 * process_table_entry:
 *   fd:
 *     fd_flags;
 *     file_pointer;
 *   fd;
 * process_table_entry;
 *
 * file_table_entry:
 *     file_status_flags;
 *     current_file_offset;
 *     v_node_pointer;
 * file_table_entry;
 *
 * v_node_table_entry:
 *    v_node_information;
 *    i_node_information;
 *    current_file_size;
 * v_node_table_entry;
 */
/**
 * INHERITENCE (SAME)
 * open files
 * real user id, real group id, effective user id, effective group id
 * supplementary group ids
 * process group id
 * session id
 * controlling terminal
 * set-user-id flags and set-group-id flags
 * current working directory
 * root directory
 * file mode creation mask
 * signal mask and dispositions
 * close-on-exec flag for any open file descriptors
 * environment
 * attatched shared memory segments
 * memory mappings
 * resource limits
 */
/**
 * INHERIENCE (DIFFERENT)
 * return value from fork
 * process ids
 * parent process ids
 * child's tms_utime, tms_stime, tms_cutime, and tms_cstime values are set to 0
 * file locks set by the parent are not inherited by the child
 * pending alarms are cleared fot the child
 * pending signals for the child is set to the empty set
 */
#include<stdio.h>
#include<unistd.h>

int global = 6;
char buf[] = "a write to stdout\n";

int main(int argc, char *argv[]){
	int aotovar;
	pid_t pid;

	aotovar = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		printf("write error\n");
	printf("before fork\n");

	if ((pid = fork()) < 0){
		printf("fork error\n");
		exit(1);
	}/*fork fail*/
	else if (pid == 0){
		global++;
		aotovar++;
	}/*child*/
	else {
		sleep(3);
	}/*parent*/
	printf("pid = %d, global = %d, aotovar = %d\n", getpid(), global, aotovar);
	exit(0);
}/*main*/
