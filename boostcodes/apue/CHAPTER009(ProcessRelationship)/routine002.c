/**
 * SUBJECT: Network Login
 * AUTHOR: LiYing
 */
/**
 * LOGIN PROCESS
 * INIT  -- fork (child)
 * INIT  -- exec getty
 * GETTY -- exec login
 * LOGIN -- shell
 * SHELL -- inetd
 * inetd -- fork (when connection request arrives from TELNET client)
 * inetd -- exec
 * telnetd -- (network connection through telnetd server and telnet client
 */

int main(int argc, char *argv[]){}/*main*/
