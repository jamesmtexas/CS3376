#include "parser.h"
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
	int incommand = 0;
	for (int i=0; i<n; i++) {
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
				break;
			case '&':
				printf("Background process: %s\n", tokens[i]);
				break;
			default:
				if (!incommand) {
					printf("Command: %s\n",tokens[i]);
					incommand = 1;
					break;
				}
				else {
					if(*tokens[i] == '-') {
						printf("Option: %s\n", tokens[i]);
					}
					else
						printf("Argument: %s\n", tokens[i]);
					break;
				}
		}
	}
}
