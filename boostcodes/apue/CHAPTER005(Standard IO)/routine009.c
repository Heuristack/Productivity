 /**
 * TITLE:
 * AUTHOR: LiYing
 * DATE:
 * NOTE:
 */
#include<stdio.h>

int main(int argc, char *argv[]){
	if (argc != 3) {
		fprintf(stderr, "usage: exec009 <directory> <prefix>\n");
		exit(-1);
	}/*failed*/

	printf("%s\n", tempnam(argv[1][0]!=' '?argv[1]:NULL, argv[2][0]!=' '?argv[2]:NULL));
	exit(0);
}/*main*/

