OPTS= -Wall -Wextra -g
OBJS= scanner.o type.o lexeme.o lexer.o int.o real.o str.o

all: scanner.o type.o lexeme.o lexer.o int.o real.o str.o
	gcc $(OPTS) $(OBJS) -o scanner

scanner.o: lexer.h lexeme.h type.h int.h real.h str.h scanner.c
	gcc $(OPTS) -c scanner.c

type.o: type.h int.h real.h str.h type.c
	gcc $(OPTS) -c type.c

lexeme.o: lexeme.h int.h real.h str.h type.h lexeme.c
	gcc $(OPTS) -c lexeme.c

lexer.o: lexer.h lexeme.h type.h lexer.c
	gcc $(OPTS) -c lexer.c
	
int.o: int.h int.c
	gcc $(OPTS) -c int.c

real.o: real.h real.c
	gcc $(OPTS) -c real.c

str.o: str.h str.c
	gcc $(OPTS) -c str.c

clean:
	rm -f *.o scanner

test1:
