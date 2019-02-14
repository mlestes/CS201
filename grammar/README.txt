README document for ESL by Murray Estes - 20190213

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

-To run the supplied, simple test cases, use the run rule. This tests pp using
 program.esl, file2.esl and badfile.esl (which intentionally causes an error)
    your_linux_name:$ make run

-To run the more indepth tests, use the test rule
    your_linux_name:$ make test

-Test 1 is the original program.txt file used to demonstrate the idea for how
 the language is supposed to look. The program is correct in all ways that the
 current implementation can determine.

-Test 2 is file2.esl. It primarily tests the lexer module's ability to sift 
 through whitespace and comments accurately.

-Test 3 is a blank file. While not practical, it demonstrates that the printer
 and parser modules at minimum handle an empty parse tree gracefully.

-All code written by Murray Estes (email: mlestes1@crimson.ua.edu).

-Uses wrapper functions for types (integer, real, string) IOT minimize use of
 generic pointers while allowing for one keyword to declare any variable type.
 These wrapper functions also permit the use of one constructor and a switch
 statement, rather than a constructor for each type.

-Code optimization and corrections will occur as the semester progresses.
