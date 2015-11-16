/**
 * TITLE: print file type of each command-line argument
 * AUTHOR: LiYing
 * DATE: 2010-6-4 21:30:00
 * NOTE:
 */

#include<sys/stat.h>
#include<stdio.h>

int main(int argc, char *argv[]){
	struct stat buf;
	int i;
	char *ptr;

	for (i = 1; i < argc; i++){
		printf("%s: ", argv[1]);
		if (lstat(argv[i], &buf) < 0) {			/*lstat(char *pathname, struct stat *buf)*/
			printf("main: lstat failed\n");
			continue;
		}/*lstat failed*/

		if (S_ISREG(buf.st_mode)) ptr = "regular";		/*S_ISREG;S_ISDIR;S_ISCHR;S_ISBLK;S_ISLNK;S_ISFIFO;S_IS_SOCK*/
		else if (S_ISDIR(buf.st_mode)) ptr = "directory";
		else if (S_ISBLK(buf.st_mode)) ptr = "block special";
		else if (S_ISCHR(buf.st_mode)) ptr = "character special";
		else if (S_ISLNK(buf.st_mode)) ptr = "symbolic link";
		else if (S_ISFIFO(buf.st_mode)) ptr = "fifo";
		else if (S_ISSOCK(buf.st_mode)) ptr = "socket";
		else ptr = "unknown";

		printf("%s\n", ptr);
	}/*parse-loop*/
}/*main*/

