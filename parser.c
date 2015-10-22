#include "parser.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sysexits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int tokenize(char *input, char *tokens[]) {
	int i = 0;
	char *token = strtok(input, " ");
	while(token) {
		tokens[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	return i;
}

void parse(char *tokens[], int n) {
	char *command;
	char *args[1024];
	int incommand = 0;
	int numargs = 0;
	int i;

	for (i=0; i<n; i++) {
		switch(*tokens[i]) {
			case '|':
				printf("Pipe: %s\n",tokens[i]);
				incommand = 0;
				break;
			case '>':
				if(*tokens[i+1] == '>') {
					printf("File redirection: %s%s\n",tokens[i],tokens[i+1]);
					printf("File: %s\n",tokens[i+2]);
					i+=2;
					incommand = 0;
					break;
				}
				else {
					printf("File redirection: %s\n",tokens[i]);
					printf("File: %s\n",tokens[i+1]);
					i++;
					incommand = 0;
					break;
				}
			case '<':
				if(*tokens[i+1] == '<') {
					printf("File redirection: %s%s\n",tokens[i],tokens[i+1]);
					printf("File: %s\n", tokens[i+2]);
					i+=2;
					incommand = 0;
					break;
				}
				else {
					printf("File redirection: %s\n", tokens[i]);
					printf("File: %s\n", tokens[i+1]);
					i++;
					incommand = 0;
					break;
				}
			case ';':
				printf("End statement: %s\n", tokens[i]);
				incommand = 0;
				break;
			case '&':
				printf("Background process: %s\n", tokens[i]);
				incommand = 0;
				break;
			default:
				if (!incommand) {
					printf("Command: %s\n",tokens[i]);
					command = tokens[i];
					incommand = 1;
					numargs = 0;
					break;
				}
				else {
					if(*tokens[i] == '-') {
						printf("Options: %s\n", tokens[i]);
					}
					else
						printf("Argument: %s\n", tokens[i]);
					args[numargs] = tokens[i];
					numargs++;
					break;
				}
		}
	}
	//runcmd(command, args, numargs);
}

void runcmd(char *cmd, char *args[], int n) {
	pid_t pid;
	int status;

	args[n] = (char *)0;

	if (n == 0) {
		system(cmd);
		return;
	}

	if((pid=fork()) == -1) {
		fprintf(stderr, "shell: can't fork: %s\n", strerror(errno));
	}
	else if(pid==0) {
		execvp(cmd,args);
		fprintf(stderr, "shell: couldn't exec %s: %s\n", cmd, strerror(errno));
		exit(EX_DATAERR);
	}

	if((pid=waitpid(pid, &status, 0)) < 0) {
		fprintf(stderr, "shell: waitpiderorr: %s\n", strerror(errno));
	}
}
