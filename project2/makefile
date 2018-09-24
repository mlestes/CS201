OPTS = -Wall -Wextra -std=c99 -g
OBJS = str.o bst.o cda.o queue.o rbt.o gt.o scanner.o corpus.o trees.o

all : $(OBJS)
	@gcc $(OPTS) $(OBJS) -o trees

trees.o : str.h rbt.h gt.h scanner.h corpus.h trees.c
	@gcc $(OPTS) trees.c -c

gt.o : bst.h gt.h gt.c
	@gcc $(OPTS) gt.c -c

rbt.o : bst.h rbt.h rbt.c
	@gcc $(OPTS) rbt.c -c

bst.o : queue.h bst.h bst.c
	@gcc $(OPTS) bst.c -c

queue.o : cda.h queue.h queue.c
	@gcc $(OPTS) queue.c -c

cda.o : cda.h cda.c
	@gcc $(OPTS) cda.c -c

str.o : str.h str.c
	@gcc $(OPTS) str.c -c

scanner.o : scanner.h scanner.c
	@gcc $(OPTS) scanner.c -c

corpus.o : corpus.h corpus.c
	@gcc $(OPTS) corpus.c -c
clean :
	@rm -f *.o trees

test :
	@echo "Beginning testing..."
	@echo
	@echo "Making sure this is correct and timing it..."
	time ./trees -r shakespeare.txt shakespeare.go2 myOutput
	@diff -s -q myOutput shakespeare-r.tree
	@rm myOutput
	@echo
	@echo "Done! All tests are successful!"
