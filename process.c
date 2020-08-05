#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "process.h"

void exec_process(process *proc) {
	pid_t pid;
	int wpstat;
	int fd[2];

	if(proc->next == NULL) {
		if (execvp(proc->name, proc->arg)) {
			perror("execvp");
			exit(127);
		}
	} else {
		if (pipe(fd) == -1);
			perror("pipe");

		pid = fork();
		if (pid < 0) {
			perror("fork");
			exit(1);
		}

		if (pid) {
			if(close(fd[1]) == -1)
				perror("close");
			if(dup2(fd[0], 0) == -1)
				perror(dup2);
			if(close(fd[0]) == -1)
				perror("close");

			if (execvp(proc->name, proc->arg)) {
				perror("execvp");
				exit(127);
			}


		} else {

			if(close(fd[0]) == -1)
				perror("close");
			if(dup2(fd[1], 1) == -1)
				perror("dup2");
			if(close(fd[1]) == -1)
				perror("close");

			exec_process(proc->next);
		}
	}


}