OPTS= -Wall -Wextra -g
OBJS= recognizer.o type.o lexeme.o lexer.o int.o real.o str.o

all: recognizer.o type.o lexeme.o lexer.o int.o real.o str.o
	gcc $(OPTS) $(OBJS) -o recognizer

recognizer.o: lexer.h lexeme.h type.h int.h real.h str.h recognizer.c
	gcc $(OPTS) -c recognizer.c

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
	rm -f *.o recognizer

test1:
	@echo "Test 1: program.esl"
	./recognizer program.esl
	@echo

test2:
	@echo "Test 2: file2.esl"
	./recognizer file2.esl
	@echo

test3:
	@echo "Test 3: file3.esl"
	./recognizer file3.esl
	@echo

test4:
	./recognizer file4.esl
	@echo

test5:
	@echo "Test 5: badfile.esl"
	./recognizer badfile.esl
	@echo

run: test1 test2 test3 test4 test5
