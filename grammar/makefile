OPTS= -Wall -Wextra -g
OBJS= env.o lexer.o parse.o type.o lexeme.o int.o real.o str.o
TEST= scanner.o recognizer.o environment.o pp.o

all: $(OBJS) pp.o
	gcc $(OPTS) $(OBJS) pp.o -o pp

scanner: $(OBJS) scanner.o
	gcc $(OPTS) lexer.o lexeme.o type.o int.o str.o real.o scanner.o -o scanner

recognizer: $(OBJS) recognizer.o
	gcc $(OPTS) $(OBJS) recognizer.o -o recognizer

environment: lexeme.o type.o int.o real.o str.o env.o environment.o
	gcc $(OPTS) lexeme.o type.o int.o real.o str.o env.o environment.o -o environment

scanner.o: ./lex/lexer.h ./lex/lexeme.h ./type/type.h ./test/scanner.c
	gcc $(OPTS) -c ./test/scanner.c

recognizer.o: ./lex/lexer.h ./lex/lexeme.h ./type/type.h ./parse/parse.h ./test/recognizer.c
	gcc $(OPTS) -c ./test/recognizer.c 

environment.o: ./env/env.h ./lex/lexeme.h ./type/type.h ./parse/parse.h ./test/environment.c
	gcc $(OPTS) -c ./test/environment.c

pp.o: ./lex/lexeme.h ./type/type.h ./type/int.h ./type/real.h ./type/str.h ./test/pp.c
	gcc $(OPTS) -c ./test/pp.c

env.o: ./env/env.h ./type/type.h ./lex/lexeme.h ./env/env.c
	gcc $(OPTS) -c ./env/env.c

lexer.o: ./lex/lexer.h ./lex/lexeme.h ./lex/lexer.c
	gcc $(OPTS) -c ./lex/lexer.c

parse.o: ./parse/parse.h ./lex/lexer.h ./lex/lexeme.h ./type/type.h ./type/str.h ./parse/parse.c
	gcc $(OPTS) -c ./parse/parse.c

type.o: ./type/type.h ./type/int.h ./type/real.h ./type/str.h ./type/type.c
	gcc $(OPTS) -c ./type/type.c

lexeme.o: ./lex/lexeme.h ./type/int.h ./type/real.h ./type/str.h ./type/type.h ./lex/lexeme.c
	gcc $(OPTS) -c ./lex/lexeme.c
	
int.o: ./type/int.h ./type/int.c
	gcc $(OPTS) -c ./type/int.c

real.o: ./type/real.h ./type/real.c
	gcc $(OPTS) -c ./type/real.c

str.o: ./type/str.h ./type/str.c
	gcc $(OPTS) -c ./type/str.c

clean:
	rm -f *.o pp environment recognizer scanner

run:
	@echo "pretty printing program.esl"
	./pp ./test/program.esl
	@echo
	@echo "pretty printing file2.esl"
	-./pp ./test/file2.esl
	@echo
	@echo "Pretty printing badfile.esl - expect an error"
	-./pp ./test/badfile.esl
	@echo

envtest:
	-./environment

recogtest:
	-./recognizer ./test/program.esl
	-./recognizer ./test/file2.esl
	-./recognizer ./test/file3.esl
	-./recognizer ./test/file4.esl
	-./recognizer ./test/badfile.esl

scantest:
	-./scanner ./test/program.esl
	-./scanner ./test/file2.esl
	-./scanner ./test/file3.esl
	-./scanner ./test/file4.esl
	-./scanner ./test/badfile.esl