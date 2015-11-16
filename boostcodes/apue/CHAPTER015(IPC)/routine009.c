/**
 * TITLE: Program to drive the add2 filter
 * AUTHOR: LiYing
 * DATE: 2010-5-12 15:47:09
 * NOTE: What is the reason for NOT running successfully?
 */
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define MAXLINE 1024

static void sig_pipe(int);		/*signal handler*/

int main(int argc, char *argv[]){
	int n, fd1[2], fd2[2];
	pid_t pid;
	char line[MAXLINE];

	if (signal(SIGPIPE, sig_pipe) == SIG_ERR){
		printf("signal failed\n");
		exit(1);
	}/*signal-handler install error*/
	if (pipe(fd1) < 0|| pipe(fd2) < 0){
		printf("pipe failed\n");
		exit(1);
	}/*pipe-error*/

	pid = fork();
	if (pid < 0)
		perror("fork failed\n");
	else if (pid > 0){
		close(fd1[0]);
		close(fd2[1]);
		while (fgets(line, MAXLINE, stdin) != NULL) {/*read a line*/
			n = strlen(line);
			if (write(fd1[1], line, n) != n){
				fprintf(stderr, "write error\n");
				exit(1);
			}/*write to fd1*/
			if ((n = read(fd2[0], line, MAXLINE)) < 0){
				fprintf(stderr, "read error\n");
				exit(1);
			}/*read from fd2*/
			if (n == 0) {
				fprintf(stderr, "child close pipe\n");
				exit(1);
			}/*break: exit loop*/

			line[n] = '\0';				/*null-terminated*/

			if (fputs(line, stdout) == EOF){
				fprintf(stderr, "fputs error\n");
				exit(1);
			}/*write back a line*/
		}/*read&write-loop: line-by-line*/

		if (ferror(stdin)){
			fprintf(stderr, "file operation error\n");
			exit(1);
		}/*file error*/
	}/*parent*/
	else if (pid == 0){
		close(fd1[1]);
		close(fd2[0]);

		if (fd1[0] != STDIN_FILENO){
			if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO){
				fprintf(stderr, "dup2 error\n");
				exit(1);
			}/*dup2 error*/
			close(fd1[0]);
		}/*duplicate stdin*/

		if (fd2[1] != STDOUT_FILENO){
			if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO){
				fprintf(stderr, "dup2 error\n");
				exit(1);
			}/*dup2 error*/
			close(fd2[1]);
		}/*duplicate stdout*/

		if (execl("./exec010", "exec010", (char *)0) < 0){
			fprintf(stderr, "exec error\n");
			exit(1);
		}/*exec error*/

	}/*child*/
	exit(0);
}/*main*/

static void sig_pipe(int sig){
	printf("SIGPIPE caught\n");
	exit(1);
}/*signal handler for SIGPIPE*/

