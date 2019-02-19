OPTS= -Wall -Wextra -g
OBJS= env.o lexer.o parse.o type.o lexeme.o int.o real.o str.o arr.o

all: $(OBJS) eval.o
	gcc $(OPTS) $(OBJS) eval.o -o eval

eval: $(OBJS) eval.o
	gcc $(OPTS) $(OBJS) eval.o -o eval

pp: $(OBJS) pp.o
	gcc $(OPTS) $(OBJS) pp.o -o pp

scanner: $(OBJS) scanner.o
	gcc $(OPTS) lexer.o lexeme.o type.o int.o str.o real.o scanner.o -o scanner

recognizer: $(OBJS) recognizer.o
	gcc $(OPTS) $(OBJS) recognizer.o -o recognizer

environment: lexeme.o type.o arr.o int.o real.o str.o env.o environment.o
	gcc $(OPTS) lexeme.o type.o arr.o int.o real.o str.o env.o environment.o -o environment

scanner.o: ./lex/lexer.h ./lex/lexeme.h ./type/type.h ./test/scanner.c
	gcc $(OPTS) -c ./test/scanner.c

recognizer.o: ./lex/lexer.h ./lex/lexeme.h ./type/type.h ./parse/parse.h ./test/recognizer.c
	gcc $(OPTS) -c ./test/recognizer.c 

environment.o: ./env/env.h ./lex/lexeme.h ./type/type.h ./parse/parse.h ./test/environment.c
	gcc $(OPTS) -c ./test/environment.c

eval.o: ./lex/lexeme.h ./lex/lexer.h ./type/type.h ./env/env.h ./parse/parse.h ./test/eval.c
	gcc $(OPTS) -c ./test/eval.c

pp.o: ./lex/lexeme.h ./type/type.h ./type/int.h ./type/real.h ./type/str.h ./test/pp.c
	gcc $(OPTS) -c ./test/pp.c

env.o: ./env/env.h ./type/type.h ./lex/lexeme.h ./env/env.c
	gcc $(OPTS) -c ./env/env.c

lexer.o: ./lex/lexer.h ./lex/lexeme.h ./lex/lexer.c
	gcc $(OPTS) -c ./lex/lexer.c

parse.o: ./parse/parse.h ./lex/lexer.h ./lex/lexeme.h ./type/type.h ./type/str.h ./parse/parse.c
	gcc $(OPTS) -c ./parse/parse.c

type.o: ./type/type.h ./type/int.h ./type/real.h ./type/str.h ./type/arr.h ./type/type.c
	gcc $(OPTS) -c ./type/type.c

lexeme.o: ./lex/lexeme.h ./type/int.h ./type/real.h ./type/str.h ./type/type.h ./lex/lexeme.c
	gcc $(OPTS) -c ./lex/lexeme.c
	
int.o: ./type/int.h ./type/int.c
	gcc $(OPTS) -c ./type/int.c

real.o: ./type/real.h ./type/real.c
	gcc $(OPTS) -c ./type/real.c

str.o: ./type/str.h ./type/str.c
	gcc $(OPTS) -c ./type/str.c

arr.o: ./type/arr.h ./type/arr.c
	gcc $(OPTS) -c ./type/arr.c

clean:
	rm -f *.o output* eval pp environment recognizer scanner

test: test1 test2 test3

test1:
	@echo "Pretty Printer test 1:"
	@rm -f output_test1.esl output2_test1.esl
	@touch output_test1.esl
	@echo "Pretty Printing program.esl"
	./pp ./test/program.esl >> output_test1.esl
	@touch output2_test1.esl
	@echo "Pretty Printing the output from the first pretty print"
	./pp ./output_test1.esl >> output2_test1.esl
	@diff -s -q output_test1.esl output2_test1.esl
	@echo "Displaying output:"
	@cat output_test1.esl
	@echo

test2:
	@echo "Pretty Printer test 2:"
	@rm -f output_test2.esl output2_test2.esl
	@touch output_test2.esl
	@echo "Pretty Printing file2.esl"
	./pp ./test/file2.esl >> output_test2.esl
	@touch output2_test2.esl
	@echo "Pretty Printing the output the the first pretty print"
	./pp ./output_test2.esl >> output2_test2.esl
	@diff -s -q output_test2.esl output2_test2.esl
	@echo "Displaying output:"
	@cat output_test2.esl
	@echo

test3:
	@echo "Pretty Printer test 3:"
	@rm -f output_test3.esl output2_test3.esl
	@touch output_test3.esl
	@echo "Pretty Printing blank.esl"
	./pp ./test/blank.esl >> output_test3.esl
	@touch output2_test3.esl
	@echo "Pretty Printing the output of the first pretty print"
	./pp ./output_test3.esl >> output2_test3.esl
	@diff -s -q output_test3.esl output2_test3.esl
	@echo "Displaying output:"
	@cat output_test3.esl
	@echo


run:
	@echo "Testing eval..."
	./eval ./test/program.esl
	
envtest:
	-./environment

recogtest:
	-./recognizer ./test/program.esl
	@echo
	-./recognizer ./test/file2.esl
	@echo
	-./recognizer ./test/file3.esl
	@echo
	-./recognizer ./test/file4.esl
	@echo
	-./recognizer ./test/badfile.esl

scantest:
	-./scanner ./test/program.esl
	@echo
	-./scanner ./test/file2.esl
	@echo
	-./scanner ./test/file3.esl
	@echo
	-./scanner ./test/file4.esl
	@echo
	-./scanner ./test/badfile.esl