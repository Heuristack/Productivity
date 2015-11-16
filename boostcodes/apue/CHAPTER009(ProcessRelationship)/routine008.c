/**
 * SUBJECT: Shell Execution of Programs
 * AUTHOR: LiYing
 */
/**
 * ON LINUX PLATFORM
 * ps -o pid,ppid,pgid,sid,comm
 * ps -o pid,ppid,pgid,sid,comm &
 * ps -o pid,ppid,pgid,sid,comm | cat
 * ps -o pid,ppid,pgid,sid,comm | cat &
 * ps -o pid,ppid,pgid,sid,comm | cat | cat -A
 * ps -o pid,ppid,pgid,sid,comm | cat | cat -A &
 * ps -o pid,ppid,pgid,sess,tpgid,command
 * ps -o pid,ppid,pgrp,session,tpgid,comm
 */

int main(int argc, char *argv[]){}/*main*/
