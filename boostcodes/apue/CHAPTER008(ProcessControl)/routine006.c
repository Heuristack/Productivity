/**
 * SUBJECT: Process Termination - 'wait' functions
 * AUTHOR: LiYing
 * TIME: 2009-10-22 12:12:00
 */
/**
 * FUNCTION PROTOTYPE -- wait for child process to change state
 * #include<sys/wait.h>
 * int waitid(idtype_t idtype, id_t id, siginfo_t *info, int options);
 * returns: zero if OK, one on error
 */
/**
 * idtype constants for waitid
 * P_PID:  1.wait for a particular process;2.id contains the process ID of the child to wait for.
 * P_PGID: 1.wait for any child process in a particular group;2.id contains the process group ID of the children to wait for.
 * P_ALL:  1.wait for any child process;2.id is ignored
 */
/**
 * options constants for waitid (bitwise OR flags)
 * WCONTINUED: 1.Wait for a process that has previously stopped and
 *             2.has been continued, and
 *             3.whose status has not yet been reported.
 * WEXITED: 1.Wait for processes that have exited.
 * WNOHANG: 1.Return immediately instead of blocking if there is no child exit status available
 * WNOWAIT: 1.Don't destroy the child exit status;
 *          2.The child's exit status can be retrieved by a subsequent call to wait, waitid,or waitpid.
 * WSTOPPED:1.Wait for a process that has stopped and whose status has not yet been reported.
 */

#include<stdio.h>
#include<sys/wait.h>

int main(int argc, char **argv){}/*main*/
