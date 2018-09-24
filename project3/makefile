OPTS = -Wall -Wextra -std=c99 -g
OBJS = da.o edge.o vert.o set.o str.o sort.o scanner.o graph.o queue.o cda.o bst.o rbt.o io.o kruskal.o

all : $(OBJS)
	@gcc $(OPTS) $(OBJS) -o kruskal

kruskal.o : set.h edge.h vert.h graph.h da.h io.h rbt.h sort.h kruskal.c
	@gcc $(OPTS) -c kruskal.c

da.o : da.h da.c
	@gcc $(OPTS) -c da.c

set.o : set.h set.c
	@gcc $(OPTS) -c set.c

scanner.o : scanner.h scanner.c
	@gcc $(OPTS) -c scanner.c

sort.o : sort.h edge.h sort.c
	@gcc $(OPTS) -c sort.c

edge.o : edge.h io.h edge.c
	@gcc $(OPTS) -c edge.c

str.o : str.h str.c
	@gcc $(OPTS) -c str.c

vert.o : vert.h io.h da.h vert.c
	@gcc $(OPTS) -c vert.c

graph.o : graph.h sort.h vert.h edge.h set.h queue.h rbt.h graph.c
	@gcc $(OPTS) -c graph.c

bst.o : bst.h queue.h bst.c
	@gcc $(OPTS) -c bst.c

rbt.o : rbt.h bst.h rbt.c
	@gcc $(OPTS) -c rbt.c

queue.o : queue.h cda.h queue.c
	@gcc $(OPTS) -c queue.c

cda.o : cda.h cda.c
	@gcc $(OPTS) -c cda.c

io.o : io.h scanner.h io.c
	@gcc $(OPTS) -c io.c

clean :
	@rm -f $(OBJS) kruskal

test :
	@echo "Beginning testing..."
	@echo
	@./kruskal g-0-8
	@echo
	@echo "Testing completed!"
