/**
 * TITLE: Example of utime function
 * AUTHOR: LiYing
 * DATE: 2010-6-9 20:32:29
 * NOTE:
 */

/*
struct utimbuf {
	time_t	actime;			//last access time
	time_t	modtime;		//last modification time
};
*/
#include<stdio.h>
#include<fcntl.h>
#include<utime.h>

int main(int argc, char *argv[]){

	int r, i, fd;
	struct stat 	statbuf;
	struct utimbuf	timebuf;

	for (i = 1; i < argc; i++) {
		r = stat(argv[i], &statbuf);				/*gain the access/modification/status-changed times*/
		if (r < 0) {
			fprintf(stderr, "stat failed\n");
			continue;
		}/*stat failed*/

		fd = open(argv[i], O_RDWR | O_TRUNC);		/*truncate file length to zero*/
		if (fd < 0) {
			fprintf(stderr, "open failed\n");
			continue;
		}/*open-failed*/
		close(fd);

		timebuf.actime = statbuf.st_atime;
		timebuf.modtime = statbuf.st_mtime;
		r = utime(argv[i], &timebuf);				/*set access and modification times*/
		if (r < 0) {
			fprintf(stderr, "utime failed\n");
			continue;
		}/*failed*/
	}/*argument-traverse*/
	exit(0);
}/*main*/

/*
ls -l  changemod times		last-modification time
ls -lu changemod times		last-access time
ls -lc changemod times		last changed-status time
*/
