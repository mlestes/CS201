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
	@echo "Test 1: program.txt"
	@./scanner program.txt

test2:
	@echo "Test 2: file2"
	@./scanner file2

test3:
	@echo "Test 3: file3"
	@./scanner file3

test4:
	@echo "Test 4: file4"
	@./scanner file4

test5:
	@echo "Test 5: badfile"
	@./scanner badfile
run: test1 test2 test3 test4 test5
