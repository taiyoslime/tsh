#ifndef PROCESS_H
#define PROCESS_H

typedef struct _process {
	char *name;
	char **arg;
	struct _process *next;
} process;

void exec_process(process *proc);

#endif