/**
 * TITLE: Example of getcwd function
 * AUTHOR: LiYing
 * DATE: 2010-6-10 11:21:55
 * NOTE:
 */
#include<stdio.h>
#include<unistd.h>

main(){
	char pathname[1024];
	if (chdir("/usr/spool/uucppublic") < 0) {
		fprintf(stderr, "chdir failed\n");
		exit(-1);
	}/*chidr-failed*/

	if (getcwd(pathname, sizeof(pathname)) < 0) {
		fprintf(stderr, " failed\n");
		exit(-1);
	}/*failed*/

	printf("cwd=%s\n", pathname);
	exit(0);
}/*main*/
