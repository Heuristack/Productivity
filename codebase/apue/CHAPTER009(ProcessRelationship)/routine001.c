/**
 * SUBJECT: Terminal Login
 * AUTHOR: LiYing
 */
/**
 * LOGIN PROCESS
 * INIT  -- fork (child)
 * INIT  -- exec getty
 * GETTY -- exec login
 * LOGIN -- shell
 * SHELL -- ... (input commands)
 */
/**
 * STATES OF LOGIN -- BSD
 * init (pid == 1)
 *     1.reads /etc/ttys;
 *     2.forks once per terminal;
 *     3.create empty environment;
 * init (child process)
 *     1.exec getty
 * getty
 *     1.open terminal device(file descriptors 0, 1, 2)
 *     2.reads user name;
 *     3.initial environment set
 *     4.execle("/bin/login", "login", "-p", username, (char *)0, envp);
 * login
 *     1.change to our home directory(chdir)
 *     2.change the ownership of our terminal device(chown) so we own it
 *     3.Change the access permissions for our terminal device so we have permission to read from and write to it
 *     4.Set our group IDs by calling setgid and initgroups
 *     5.Initialize the environment with all the information that login has:
 *           our home directory (HOME), shell (SHELL), user name (USER and LOGNAME), and a default path (PATH)
 *     6.Change to our user ID (setuid) and invoke our login shell, as in
 *           execl("/bin/sh", "-sh", (char *)0);
 * login shell
 * 	   fd:0, 1, 2
 * terminal driver
 *     throuth hard-wired connection
 * user at a terminal
 */

int main(int argc, char *argv[]){}/*main*/
