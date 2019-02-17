README document for ESL by Murray Estes - 20190216

*** TRIVIA ABOUT ESL ***
-ESL is named after its file extension, *.esl. Beyond that, it has no meaning
 unless you give it one. For all I care, you can say it stands for European
 Sequined Leotard. Or Empirically Studied Liposuction. Whatever floats your
 boat.

-ESL is dynamically typed. This has several consequences in regards to its
 implementation. For example, var x can initially be a string. Later, it can be
 reassigned the integer x and still retain its original string value. I may 
 make it possible later on to recall the string value after being reassigned a
 value of a different type. (Maybe a setTypeCast function)

*** WRITING CODE IN ESL ***
-To declare a variable, use the VAR keyword. A value can be assigned 
 immediately or at a later point in time.
    
    VAR x;
    VAR y = 25;
    
-Functions by default return the most recently assigned variable. However, the 
 user may opt to return a different variable with the RETURN keyword.

    VAR x = 25;
    VAR y = 10; <-this variable will return by default if no RETURN statement
    RETURN x;

-Declare functions with the DEFINE keyword. The function does not have to be
 defined at this point.

    DEFINE foo();
    DEFINE bar(arg1 arg2)
    BEGIN

        VAR x = arg1 * arg2;

    END

 Note that the definition block begins with the BEGIN keyword and ends with
 the END keyword. All blocks function this way. Also note that the 
 paramater list is space separated, not comma separated. All lists function
 this way. (The comma is not a valid character in ESL, except in quoted
 strings.)

-Arrays are available functionally. When decaring an array, simply call the 
 builtin ARRAY() function.

    VAR arr = ARRAY();

 This will call the builtin function newArray(); The user can also call this 
 function. 
    
    VAR arr = new_array();

-User defined objects are declared with the STRUCT keyword. Their attributes
 are accessed with the DOT (.) operator.

    STRUCT object
    BEGIN
        VAR attr1;     <- this attribute does not a default value
        VAR attr2 = 1; <- this attribute has a default value of 1
    END

    VAR obj = NEW object; <- this is how to assign the object to a variable
    VAR x = obj.attr1;

-To print to the console, use the PRINT keyword (and builtin function).

    PRINT(<string>);

-To read from a file, use the READ keyword (and builtin function).

    READ(<filename>);

-To write to a file (or any output stream that isn't the console), use the 
 WRITE keyword (and builtin function).

    WRITE(<filename> <string>);

-The use of * as a pointer is valid only if it immediately precedes the 
 variable being used as a pointer. If a space is preferred, use the STAR
 keyword.

    VAR *x;
    VAR STAR x;

 The above two lines are functionally identical.

*** RUNNING ESL ***
-Will write this section once implemented.

*** THE TESTING PROGRAMS ***
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

-To use environment, use the make rule to compile, then run environment on the 
 command line.
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

*** CREDITS AND OTHER GENERAL INFORMATION ***
-All code written by Murray Estes (email: mlestes1@crimson.ua.edu).

-Uses wrapper functions for types (integer, real, string, array) IOT minimize 
 use of generic pointers while allowing for one keyword to declare any variable
 type. These wrapper functions also permit the use of one constructor and a 
 switch statement, rather than a constructor for each type.

-Code optimization and corrections will occur as the semester progresses.
