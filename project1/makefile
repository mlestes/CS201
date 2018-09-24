OPTS = -Wall -Wextra -std=c99 -g
OBJS = cda.o da.o stack.o queue.o bst.o scanner.o str.o real.o value.o convert.o matilda.o
EXES = matilda

all : $(OBJS)
	@gcc $(OPTS) $(OBJS) -o matilda -lm

cda.o : cda.h cda.c
	@gcc $(OPTS) cda.c -c

da.o : da.h da.c
	@gcc $(OPTS) da.c -c

stack.o : stack.h da.h stack.c
	@gcc $(OPTS) stack.c -c

queue.o : queue.h cda.h queue.c
	@gcc $(OPTS) queue.c -c

bst.o : bst.h bst.c
	@gcc $(OPTS) bst.c -c

scanner.o : scanner.h scanner.c
	@gcc $(OPTS) scanner.c -c

matilda.o : stack.h queue.h bst.h scanner.h convert.h str.h real.h value.h matilda.c
	@gcc $(OPTS) matilda.c -c -lm

str.o : str.h str.c
	@gcc $(OPTS) str.c -c

real.o : real.h real.c
	@gcc $(OPTS) real.c -c

value.o : value.h value.c
	@gcc $(OPTS) value.c -c

convert.o : convert.h str.h real.h value.h convert.c
	@gcc $(OPTS) convert.c -c -lm

clean :
	@rm -f $(OBJS) $(EXES)

test :
	./matilda -v
	./matilda -p testfile
	./matilda -i numfile
	./matilda -b trueextreme
	./matilda baddec
	./matilda -p -i -b extremepar
