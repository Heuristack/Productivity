/**
 * SUBJECT: Single-Instance Daemons
 * AUTHOR: LiYing
 */
/**
 * file-locking && record-locking
 * convenient mutual-exclusion mechanism
 */
/**
 * EXAMPLE -- ENSURE ONLY ONE COPY OF A DAEMON IS RUNNING
 *
 */
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

extern int lockfile(int);

int already_running(void){
	int     fd;
    char    buf[16];

    fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
    if (fd < 0) {
        syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }/*open failed*/
    if (lockfile(fd) < 0) {
        if (errno == EACCES || errno == EAGAIN) {
            close(fd);
            return(1);
        }
        syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }/*lock file failed*/

    ftruncate(fd, 0);

    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf)+1);

    return(0);
}/*already_running*/
