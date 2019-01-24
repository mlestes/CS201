Lexer for ESL by Murray Estes - 20190123
-Scanner reads a file and prints out each token and the type of lexeme.

-All included *.c and *.h files are required for the scanner and included
 makefile to function. The included test files are required for the run rule.

-To use the scanner, use the make rule to compile.
 Then, on the command line, use scanner <file>.

-Example commands
your_linux_name:$ make
your_linux_name:$ ./scanner <program>
//some output

-To run the supplied test cases, use the run rule
your_linux_name:$ make run
//test1
//test2
//test3
//test4
//test5

-All code written by Murray Estes (email: mlestes1@crimson.ua.edu).

-Uses wrapper functions for types (integer, real, string) IOT minimize use of
 generic pointers while allowing for one keyword to declare any variable type.
 These wrapper functions also permit the use of one constructor and a switch
 statement, rather than a constructor for each type.

-Code optimization and corrections will occur as the semester progresses
