#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "parse.h"
#include "commands.h"

int main(int argc, char **argv, char **environ) {
	pid_t pid;
	int wpstat;

	while (1) {
		process* proc = read_line();
		bool exec_buildin_cmd = false;

		for(int i = 0; commands[i].name && commands[i].func; i++) {
			if(!strcmp(commands[i].name, proc->name)){
				(commands[i].func)(proc->arg);
				exec_buildin_cmd = true;
				break;
			}
		}

		if(!exec_buildin_cmd) {
			pid = fork();
			if (pid < 0) {
				perror("fork");
				exit(1);
			}

			if (pid) {
				waitpid(pid, &wpstat, WUNTRACED);
				if(!strcmp(proc->name, "exit")){
					exit(0);
				}

			} else {
				if (!exec_buildin_cmd && execvp(proc->name, proc->arg)) {
					perror("execvp");
					exit(127);
				}
			}
		}
	}
}