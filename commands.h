#ifndef __COMMANDS__
#define __COMMANDS__

#include <stddef.h>

void cmd_cd(const char** arg);
void cmd_exit(const char** arg);

typedef struct {
	char *name;
	void (*func)(const char**);
} command;

const command commands[] = {
	{"cd", cmd_cd},
	{"exit", cmd_exit},
	{NULL, NULL}
};

#endif