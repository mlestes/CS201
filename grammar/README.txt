README document for ESL by Murray Estes - 20190210
-Scanner performs a simple functions check for the lexer module.

-Recognizer performs an in-depth functions check for the parser module.

-Environment performs a simple functions check for the environment module, 
 testing all possible cases and ends with an error (checking out of scope).

-PP is a not-so Pretty Printer. It tests the ability to read the parse tree. It 
 does not interact with the environment module.

-To use scanner, first compile it using the make rule, then run scanner <file> 
 on the command line.
    your_linux_name:$ make scanner
    your_linux_name:$ ./scanner <file_name>

-To use environment, use the make rule to compile.
    your_linux_name:$ make environment
    your_linux_name:$ ./environment

-To use recognizer, compile it with the make rule, then run recognizer <file>
 on the command line.
    your_linux_name:$ make recognizer
    your_linux_name:$ ./recognizer <file_name>

-To use pp, compile it with the make rule, then run pp <file> on the command 
 line.
    your_linux_name:$ make pp
    your_linux_name:$ ./pp <file_name>

-The current "make all" rule compiles pp.

-To run the supplied test cases, use the run rule
    your_linux_name:$ make run

-All code written by Murray Estes (email: mlestes1@crimson.ua.edu).

-Uses wrapper functions for types (integer, real, string) IOT minimize use of
 generic pointers while allowing for one keyword to declare any variable type.
 These wrapper functions also permit the use of one constructor and a switch
 statement, rather than a constructor for each type.

-Code optimization and corrections will occur as the semester progresses.
