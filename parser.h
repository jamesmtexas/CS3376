#ifndef PARSER_H
#define PARSER_H

int tokenize(char *input, char *tokens[]);
void parse(char *tokens[], int n);
void runcmd(char *cmd, char *args[], int n);
void startpipe(char *cmd, char *args[], int n);

#endif
