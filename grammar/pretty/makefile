OPTS= -Wall -Wextra -g
OBJS= pp.o env.o lexer.o parse.o type.o lexeme.o int.o real.o str.o

all: $(OBJS)
	gcc $(OPTS) $(OBJS) -o pp

pp.o: lexeme.h type.h int.h real.h str.h pp.c
	gcc $(OPTS) -c pp.c

env.o: env.h type.h lexeme.h env.c
	gcc $(OPTS) -c env.c

lexer.o: lexer.h lexeme.h lexer.c
	gcc $(OPTS) -c lexer.c

parse.o: parse.h lexer.h lexeme.h type.h str.h parse.c
	gcc $(OPTS) -c parse.c

type.o: type.h int.h real.h str.h type.c
	gcc $(OPTS) -c type.c

lexeme.o: lexeme.h int.h real.h str.h type.h lexeme.c
	gcc $(OPTS) -c lexeme.c
	
int.o: int.h int.c
	gcc $(OPTS) -c int.c

real.o: real.h real.c
	gcc $(OPTS) -c real.c

str.o: str.h str.c
	gcc $(OPTS) -c str.c

clean:
	rm -f *.o pp

run:
	@echo "pretty printing program.esl"
	./pp program.esl
	@echo
	@echo "pretty printing file2.esl"
	-./pp file2.esl
	@echo
	@echo "Pretty printing badfile.esl - expect an error"
	-./pp badfile.esl
	@echo