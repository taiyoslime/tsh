#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "process.h"
#include "parse.h"
#include "commands.h"

#define PROMPT "$ "

int main(int argc, char **argv, char **environ) {

	while (1) {
		pid_t pid;
		int wpstat;
		printf(PROMPT);

		process* proc = read_line();
		if (!(strcmp(proc->name, NOP)))
			continue;

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
				waitpid(-1, &wpstat, WUNTRACED);

			} else {
				exec_process(proc);
			}
		}
	}
}