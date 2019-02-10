Environment for ESL by Murray Estes - 20190125
-Environment performs a simple functions check for the environment module ISO
 ESL, testing all possible cases and ends with an error (checking out of scope).

-To use environment, use the make rule to compile.
 Then, on the command line, use environment.

-Example commands
your_linux_name:$ make
your_linux_name:$ ./environment
//some output

-To run the supplied test cases, use the test rule
your_linux_name:$ make test

-All code written by Murray Estes (email: mlestes1@crimson.ua.edu).

-Uses wrapper functions for types (integer, real, string) IOT minimize use of
 generic pointers while allowing for one keyword to declare any variable type.
 These wrapper functions also permit the use of one constructor and a switch
 statement, rather than a constructor for each type.

-Code optimization and corrections will occur as the semester progresses.
