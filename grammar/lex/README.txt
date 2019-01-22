Lexer for Murray Estes
-Uses wrapper functions for types (integer, real, string) IOT minimize use of
 generic pointers while allowing for one keyword to declare any variable type.
-Scanner reads a file and prints out each token and the type of lexeme.
-To use the scanner, use the make rule to compile.
 Then, on the command line, use scanner <file>.
-Example commands
TDC:$ make
TDC:$ scanner program
//some output

-To run the supplied test cases, use the run rule
TDC:$ make run
//test1
//test2
//test3
//test4
//test5

-All code written by Murray Estes.
-Code optimization and corrections will occur as the semester progresses
