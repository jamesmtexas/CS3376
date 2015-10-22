shell: shell.o parser.o
	gcc -o shell shell.o parser.o
	
shell.o: shell.c parser.h
	gcc -c shell.c
	
parser.o: parser.c parser.h
	gcc -c parser.c