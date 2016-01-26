 /**
 * TITLE: Turn on one or more of the file status flags for a descriptor
 * AUTHOR: LiYing
 * DATE: 2010-6-13 10:04:25
 * NOTE:
 */
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	exit(0);
}/*main*/

int setflagon_fs(int fd, int flags){
	int fs;
	fs = fcntl(fd, F_GETFL, 0);
	if (fs < 0) {
		fprintf(stderr, "fcntl failed\n");
		return (-1);
	}/*failed*/

	fs |= flags;		/*turn on flags*/

	fs = fcntl(fd, F_SETFL, fs);
	if (fs < 0) {
		fprintf(stderr, "fcntl failed\n");
		return (-1);
	}/*failed*/
	return fs;
}/*setflagon_fs*/

int setflagoff_fs(int fd, int flags){
	int fs;
	fs = fcntl(fd, F_GETFL, 0);
	if (fs < 0) {
		fprintf(stderr, "fcntl failed\n");
		return (-1);
	}/*failed*/

	fs &= ~flags;		/*turn on flags*/

	fs = fcntl(fd, F_SETFL, fs);
	if (fs < 0) {
		fprintf(stderr, "fcntl failed\n");
		return (-1);
	}/*failed*/
	return fs;
}/*setflagoff_fs*/
