#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "parser.h"

char *getinput(char *buffer, size_t buflen, char *prompt) {
	printf(prompt);
	return fgets(buffer, buflen, stdin);
}

int main(int argc, char **argv) {
	char buf[1024];
	char *tokens[1024]; 
	char prompt[1024] = "$$ ";
	pid_t pid;
	int status;

	while(getinput(buf,sizeof(buf), prompt)) {
		buf[strlen(buf) - 1] = '\0';

		if(!strcmp(buf, "exit") || !strcmp(buf, "quit")) {
			exit(EX_OK);
		}
		if(!strcmp(buf, "list")) {
			system("ls");
			continue;
		}
		if(!strncmp(buf, "prompt", 6)) {
			int i;
			for (i = 8; buf[i] != '"'; i++) {
				prompt[i-8] = buf[i];
			}
			prompt[i-7] = '\0';
			continue;
		}

		int numtokens;

		numtokens = tokenize(buf, tokens);
		parse(tokens,numtokens);

	}
	exit(EX_OK);
}
