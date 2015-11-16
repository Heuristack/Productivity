/**
 * TITLE: Send data from parent to child over a pipe
 * AUTHOR: LiYing
 * DATE: 2010-5-11 11:37:12
 * NOTE: 1.pipes are halfduplex; 2.pipes are only used between related processes
 */
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int fd[2];
	int n;
	int r;
	char line[0xff];

	r = pipe(fd);
	if (r < 0)
		perror("main: pipe failed\n");
	pid = fork();
	if (pid < 0)
		perror("main: fork failed\n");
	else if (pid > 0){
		close(fd[0]);
		write(fd[1], "hello world\n", 12);
	}/*parent*/
	else if (pid == 0){
		pid = getpid();
		close(fd[1]);
		n = read(fd[0], line, 0xff);
		printf("child[%d] say: \n", pid);
		write(STDIN_FILENO, line, n);
	}/*child*/
	exit(1);
}/*main*/

