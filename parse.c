#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "parse.h"

static process *parse(char *buf) {

	process *proc;

	if ((proc = (process*) malloc(sizeof(process))) == NULL)
		return NULL;

	char **tokens;
	int tokens_len = 4;
	if ((tokens = (char**) malloc(sizeof(char*) * tokens_len)) == NULL)
		return NULL;

	char *token = strtok(buf, " \n");
	for (int i = 0; token != NULL; i++) {
		int token_len = strlen(token);
		if ((tokens[i] = (char*) malloc(sizeof(char) * token_len)) == NULL)
			return NULL;
		memcpy(tokens[i], token, token_len);

		if ( i + 1 == tokens_len ) {
			tokens_len *= 2;
			char** tmp = (char**) realloc(tokens, sizeof(char*) * tokens_len);
			if (tmp == NULL) {
				free(tokens);
				return NULL;
			}
			tokens = tmp;
			tmp = NULL;
		}

		tokens[i+1] = NULL;
		token = strtok(NULL, " \n");
	}

	proc->arg = tokens;
	proc->name = proc->arg[0];

	return proc;
}

process *read_line() {
	char *buf;
	printf(PROMPT);

	if ((buf = (char*) malloc(sizeof(char) * BUFSIZE)) == NULL)
		perror("read_line");

	fgets(buf, BUFSIZE, stdin);

	process* proc = parse(buf);
	if (proc == NULL)
		perror("parse");

	return proc;
}

