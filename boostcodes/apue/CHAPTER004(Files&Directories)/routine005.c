/**
 * TITLE: Open a file and then unlink it
 * AUTHOR: LiYing
 * DATE: 2010-6-9 20:03:51
 * NOTE:
 */
#include<stdio.h>
#include<fcntl.h>

main(){
	int r;
	r = open("tempfile", O_RDWR);			/*open the file*/
	if (r < 0) {
		fprintf(stderr, "open failed\n");
		exit(-1);
	}/*open-failed*/
	r = unlink("tempfile");					/*unlink the file: delete the dirent*/
	if (r < 0) {
		fprintf(stderr, "unlink failed\n");
		exit(-1);
	}/*unlink-failed*/
	printf("file unlinked\n");				/*the file unlinked but not deleted*/
	sleep(15);
	printf("done\n");
	exit(0);
}/*main*/
