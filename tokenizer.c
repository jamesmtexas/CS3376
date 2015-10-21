#include "tokenizer.h"

void tokenize(char *input, char **output ) {

	int i=0;
	int j=0;

	for(char *iterator = input; iterator!=0; iterator++) {
		if (*iterator == ' ') {
			output[i][j] = 0;
			i++;
		}
		else if(*iterator == '|') {
			//pipe
		}
		else if(*iterator == '>' || '<') {
			//redirect
		}
		else if(*iterator == ';') {
			//end statement
		}
		else {
			output[i][j] = *iterator;
		}

		j++;
	}
}
