#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void cmd_cd(const char** arg) {
	int ch;
	if (arg[1] == NULL) {
		ch  = chdir("~");
	}
	else {
		ch = chdir(arg[1]);
	}
	if (ch) perror("chdir");
}

void cmd_exit(const char** arg) {
	printf("bye\n");
	exit(0);
}