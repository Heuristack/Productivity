/**
 * TITLE: Using two pipes for parentchild synchronization
 * AUTHOR: LiYing
 * DATE: 2010-5-12 10:01:11
 * NOTE: relationship between pipe and signal (pipe could simulate signal because of read blocking)
 */
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

static int fd1[2], fd2[2];

void TELL_WAIT(void){
	if (pipe(fd1) < 0 || pipe(fd2) < 0){
		perror("TELL_WAIT: pipe failed\n");
		exit(1);
	}/*pipe failed*/
}/*TELL_WAIT*/

void TELL_PARENT(pid_t pid){
	if (write(fd2[1], "c", 1) != 1){
		perror("TELL_PARENT: write error\n");
		exit(1);
	}/*write*/
}/*TELL_PARENT*/

void WAIT_PARENT(void){
	int c;
	if (read(fd1[0], &c, 1) != 1){
		perror("WAIT_PARENT: read error\n");
		exit(1);
	}/*read block*/
	if (c != 'p')
		perror("WAIT_PARENT: incorrent data\n");
}/*WAIT_PARENT*/

void TELL_CHILD(pid_t pid){
	if (write(fd1[1], "p", 1) != 1){
		perror("TELL_CHILD: write error\n");
		exit(1);
	}/*write*/
}/*TELL_CHILD*/

void WAIT_CHILD(void){
	int c;
	if (read(fd2[0], &c, 1) != 1){
		perror("WAIT_CHILD: read error\n");
		exit(1);
	}/*read block*/
}/*WAIT_CHILD*/

int main(int argc, char *argv[]){
	pid_t pid;
	TELL_WAIT();
	pid = fork();
	if (pid < 0)
		perror("fork failed\n");
	else if (pid > 0){		/*parent*/
		printf("parent: waiting child...\n");
		WAIT_CHILD();
		printf("parnet: waited child.\n");
		wait(NULL);
		exit(0);
	}/*parent*/
	else if (pid == 0){		/*child*/
		sleep(2);
		TELL_PARENT(pid);
		printf("child: tell parent\n");
		exit(0);
	}/*child*/
}/*main*/


