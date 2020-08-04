#ifndef __PARSE__
#define __PARSE__

#define PROMPT "$ "
#define BUFSIZE 256

typedef struct {
	char *name;
	char **arg;
} process;

process *read_line(void);

#endif