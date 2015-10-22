#include "parser.h"
#include <unistd.h>

void parse(char *input, char *tokens[]) {

}

void prepforexec(char *command, char *arguments[]) {

	int argNum = 0;
	int j = 0;
	int i = 0;
	for(i=0; command[i] != '\0'; i++) {
		if(command[i] == ' ') {
			arguments[argNum][j+1] = '\0';
			argNum++;
			j=0;
		}
		else
		{
			arguments[argNum][j] = command[i];
			j++;
		}
	}

	execvp(arguments[0], arguments+1);
}
