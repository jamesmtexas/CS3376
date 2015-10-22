#ifndef PARSER_H
#define PARSER_H

int tokenize(char *input, char *tokens[]);
void parse(char *tokens[], int n);

#endif
