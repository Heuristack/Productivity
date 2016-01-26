/**
 * TITLE:  Copy file to pager program
 * AUTHOR: LiYing
 * DATE: 2010-5-11 14:24:12
 * NOTE: passing arguments to execs programs through pipe
 */

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>

#define DEF_PAGER "/bin/more"
#define MAXLINE 1024

int main(int argc, char *argv[]){
	int fd[2];
	pid_t pid;
	FILE *fp;
	char line[MAXLINE];
	int n;
	char *pager, *argv0;

	if (argc != 2){
		printf("usage: %s <pathname>\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL){
		perror("fopen failed\n");
		exit(1);
	}

	if (pipe(fd) < 0){
		perror("pipe failed\n");
		exit(1);
	}

	pid = fork();
	if (pid < 0)
		perror("fork failed\n");
	else if (pid > 0){
		close(fd[0]);

		while(fgets(line, MAXLINE, fp) != NULL){
			n = strlen(line);
			if (write(fd[1], line, n) != n){
				perror("wirte failed\n");
				exit(1);
			}
		}/*write into pipe*/
		close(fd[1]);

		if (waitpid(pid, NULL, 0) < 0){
			perror("wait failed\n");
			exit(1);
		}
		exit(0);
	}/*parent*/
	else if (pid == 0){
		close(fd[1]);
		if (fd[0] != STDIN_FILENO){
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO){
				perror("dup2 failed\n");
				exit(1);
			}/*dup fd[0] onto stdin*/
			close(fd[0]);
		}/**/

		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;
		else
			argv0 = pager;

		printf("pager is %s\n", pager);
		printf("argv0 is %s\n", argv0);
		if (execl(pager, argv0, (char *)0) < 0){
			perror("execl failed\n");
			exit(1);
		}/*exec the command*/
	}/*child*/
	exit(0);
}/*main*/

