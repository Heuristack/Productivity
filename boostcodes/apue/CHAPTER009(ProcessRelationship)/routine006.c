/**
 * SUBJECT: tcgetpgrp, tcsetpgrp, tcgetsid Functions
 * AUTHOR: LiYing
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * pid_t tcgetpgrp(int filedes);
 * returns: process group id of foreground process group if OK, minus one on error
 * int tcsetpgrp(int filedes, pid_t pgrpid);
 * returns: zero if OK, minus one on error
 */
/**
 * SYNOPSIS
 * 1. The function tcgetpgrp returns the process group ID of the foreground process group
 *    associated with the terminal open on filedes
 * 2. If the process has a controlling terminal, the process can call tcsetpgrp to set the
 *    foreground process group ID to pgrpid. The value of pgrpid must be the process group ID of
 *    a process group in the same session, and filedes must refer to the controlling terminal of the session.
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * pid_t tcgetsie(int filedes);
 * returns: session leader's process group id if OK, minus one on error
 */
/**
 * SYNOPSIS
 * identify the session ID of the controlling terminal's session leader
 * (which is equivalent to the session leader's process group ID)
 */

int main(int argc, char *argv[]){
}/*main*/
