/**
 * TITLE: Streams and FILE Objects
 * AUTHOR: LiYing
 * DATE: 2010-6-11 19:02:54
 * NOTE: If the orientation of the stream has already been determined, fwide does not change it.
 */

#include<stdio.h>
#include<wchar.h>

main(){
	int r;
	FILE *fp;

	fp = fopen("./routine001.c", "r");

	fprintf(stderr, "main: the stream is %s-oriented\n", (fwide(fp, 0) > 0)?"wide":"byte");

	/*orientation determination first time ?*/
	fprintf(stderr, "main: fwide setting wide-oriented: %d\n", fwide(fp, 1));

	fprintf(stderr, "main: the stream is %s-oriented\n", (fwide(fp, 0) > 0)?"wide":"byte");

	/*can not be changed except reopen the stream*/
	fprintf(stderr, "main: fwide setting byte-oriented: %d\n", fwide(fp, -1));

	fprintf(stderr, "main: the stream is %s-oriented\n", (fwide(fp, 0) > 0)?"wide":"byte");

}/*main*/
