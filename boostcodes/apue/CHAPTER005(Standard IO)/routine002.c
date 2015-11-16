/**
 * TITLE: Buffering-Orientation
 * AUTHOR: LiYing
 * DATE: 2010-6-11 19:14:04
 * NOTE: three type of buffering: fully-buffered; line-buffered; unbuffered;
 */
#include<stdio.h>

int main(int argc, char *argv[]){
	char buf[0xfff];
	int size = 0xfff;
	FILE *fp;

	fp = fopen("routine001.c", "r");
										//buffering or not (setbuf set buffer on or off)
	setbuf(fp, buf);					//using buf with length BUFSIZ (fully-buffered or line-buffered)
	setbuf(fp, NULL);					//no buffer (unbuffer)

										//1.buffer or not: _IOUBF;2.buffer is NULL or not;3.mode;
	setvbuf(fp, buf, _IOFBF, size);		//using buf with length size (fully-buffered)
	setvbuf(fp, NULL, _IOFBF, size);	//system buffer of appropriate length (fully-buffered)

	setvbuf(fp, buf, _IOLBF, size);		//using buf with length size (line-buffered)
	setvbuf(fp, NULL, _IOLBF, size);	//system buffer of appropriate length (line-buffered)

	setvbuf(fp, buf, _IONBF, size);		//no buffer (unbuffered)
	setvbuf(fp, NULL, _IONBF, size);	//no buffer (unbuffered)

	fp = freopen("routine001.c", "r+", fp);
	return 0;
}/*main*/
