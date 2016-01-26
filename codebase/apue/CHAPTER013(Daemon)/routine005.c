/**
 * SUBJECT: Daemons
 * AUTHOR: LiYing
 */

/**
 * DAEMON CONVENTIONS
 * (a) If the daemon uses a lock file, the file is usually stored as /var/run/name.pid
 * (b) If the daemon supports configuration options, they are usually stored in /etc/name.conf
 * (c) Daemons can be started from the command line, but they are usually started from one of the system initialization scripts (/etc/rc* or /etc/init.d/*).
 * (d) If a daemon has a configuration file, the daemon reads it when it starts, but usually won't look at it again.
 */

/**
 * EXAMPLE -- Alternate implementation of daemon rereading configuration files
 *
 */

int main(){}/*main*/
