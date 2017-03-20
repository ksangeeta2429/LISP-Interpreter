#comment
FLAG=-c -w -g 
CC=gcc

Interpreter:main.o scanner.o parser.o evaluate.o
	$(CC) main.o scanner.o parser.o evaluate.o -o Interpreter

main.o:main.c header.h
	$(CC) $(FLAG) main.c -I ./

scanner.o:scanner.c header.h
	$(CC) $(FLAG) scanner.c -I ./

parser.o:parser.c header.h 
	$(CC) $(FLAG) parser.c -I ./

evaluate.o:evaluate.c header.h
	$(CC) $(FLAG) evaluate.c -I ./
    
clean:
	rm ./*.o
	rm ./Interpreter
	rm output.txt
