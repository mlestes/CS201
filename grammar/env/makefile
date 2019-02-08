OPTS= -Wall -Wextra -g
OBJS= environment.o env.o type.o lexeme.o int.o real.o str.o

all: $(OBJS)
	gcc $(OPTS) $(OBJS) -o environment

environment.o: lexeme.h type.h int.h real.h str.h environment.c
	gcc $(OPTS) -c environment.c

env.o: env.h type.h lexeme.h env.c
	gcc $(OPTS) -c env.c

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
	rm -f *.o environment

run:
	-./environment