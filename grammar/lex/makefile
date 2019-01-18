OPTS= -Wall -Wextra -g
OBJS= scanner.o type.o lexeme.o lexer.o
all:
	gcc $(OPTS) $(OBJS) -o scanner

scanner.o: lexer.h lexeme.h type.h scanner.c
	gcc $(OPTS) -c scanner.c

type.o: type.h type.c
	gcc $(OPTS) -c type.c

lexeme.o: lexeme.h type.h lexeme.c
	gcc $(OPTS) -c lexeme.c

lexer.o: lexer.h lexeme.h type.h lexer.c
	gcc $(OPTS) -c lexer.c
	
clean:
	rm -f *.o scanner

test1:
