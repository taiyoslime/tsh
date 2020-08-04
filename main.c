#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "parse.h"

extern char **environ;

int main(void) {
	pid_t pid;
	int wpstat;

	while (1) {
		process* proc = read_line();
		pid = fork();
		if (pid < 0) {
			perror("fork");
			exit(1);
		}

		if (pid) {
			waitpid(pid, &wpstat, WUNTRACED);
		} else {
			if (execve(proc->name, proc->arg, environ)) {
				perror("execve");
				exit(127);
			}
		}
	}
}