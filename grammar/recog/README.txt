Recognizer for ESL by Murray Estes - 20190125
-Recognizer reads a .esl file and either prints that a program is correct or
 an error.

-All included *.c and *.h files are required for the recognizer and included
 makefile to function. The included test files are required for the run and 
 test rules.

-To use the recognizer, use the make rule to compile.
 Then, on the command line, use recognizer <file>. Note that filenames must
 have the .esl extension in order for the recognizer to read them. It will 
 return an error if the extension is missing or otherwise incorrect.

-Example commands
your_linux_name:$ make
your_linux_name:$ ./recognizer program.esl
//some output

-A make run rule is supplied, however, it will stop at test3, since the
 recognizer returns an error for that test. "make test" functions the same as
 "make run".

-To run the supplied test cases, use the test rules
your_linux_name:$ make test1
//test1

your_linux_name:$ make test2
//test2

your_linux_name:$ make test3
//test3

your_linux_name:$ make test4
//test4

your_linux_name:$ make test5
//test5

-Tests 1 and 2 should parse with no error.

-Test 1 is the original program.txt file submitted as an example of the
 language.

-Test 2 is testing the lexer's ability to handle comments.

-Test 3 should indicate a missing semi-colon.

-Test 4 should indicate a missing END keyword at the end of a nested function.

-Test 5 should in some way complain about the DEFINE keyword being misspelt/
 missing. In my testing, it complains about looking for END_READ when it
 recieves a VARIABLE. This is because the lexer parses the misspelt token
 (DE|INE) as "DE", which it recognizes as a VARIABLE. Because the recognizer is
 looking for either of the "DEFINE" or "VAR" or "STRUCT" keywords and not "DE",
 it assumes there isn't a program so it looks for "END_READ", which isn't "DE".

-All code written by Murray Estes (email: mlestes1@crimson.ua.edu).

-Uses wrapper functions for types (integer, real, string) IOT minimize use of
 generic pointers while allowing for one keyword to declare any variable type.
 These wrapper functions also permit the use of one constructor and a switch
 statement, rather than a constructor for each type.

-Code optimization and corrections will occur as the semester progresses.
