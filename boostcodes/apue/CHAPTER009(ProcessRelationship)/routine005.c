/**
 * SUBJECT: Controlling Terminal
 * AUTHOR: LiYing
 */
/**
 * CHARACTERISTICS OF SESSIONS && PROCESS GROUPS
 * 1.controlling terminal: a session has a controlling terminal.
 * 2.controlling process: session leader connects to the controlling terminal is controlling process
 * 3.one foreground process group && more background process groups
 * 4.If a session has a controlling terminal, it has a single foreground process group, and
 *   all other process groups in the session are background process groups.
 * 5.terminal's interrupt key: interrupt signal sent to all processes in foreground process group
 * 6.terminal's quit key: quit signals sent to all processes in foreground process group
 * 7.If a modem (or network) disconnect is detected by the terminal interface, the hang-up signal
 *   is sent to the controlling process (the session leader).
 */
/**
 *
 *
 */

int main(int argc, char *argv[]){}/*main*/
