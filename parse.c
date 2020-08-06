#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "parse.h"

static process *parse(char *buf) {
	process *prev_proc = NULL;
	int i = 0;

	for(char *buf_l, *_proc_char = strtok_r(buf, "|", &buf_l); _proc_char != NULL; _proc_char = strtok_r(NULL, "|", &buf_l)) {

		char *proc_char;

		if ((proc_char = (char*) malloc(sizeof(char) * strlen(_proc_char))) == NULL)
			return NULL;

		memcpy(proc_char, _proc_char, strlen(_proc_char));

		process *proc;
		if ((proc = (process*) malloc(sizeof(process))) == NULL)
			return NULL;

		char **tokens;
		int tokens_len = 4;
		if ((tokens = (char**) malloc(sizeof(char*) * tokens_len)) == NULL)
			return NULL;

		char *proc_char_l, *token = strtok_r(proc_char, " \n", &proc_char_l);
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
			token = strtok_r(NULL, " \n", &proc_char_l);
		}

		proc->arg = tokens;
		proc->name = proc->arg[0];
		proc->next = prev_proc;

		prev_proc = proc;
	}

	return prev_proc;
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

