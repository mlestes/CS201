/*****************************************************************************/
// environment.c by Murray Estes
// A program to test the environment implementation for ESL
// Begin Date: 20190207
// Complete Date:
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "lexeme.h"
#include "env.h"
#include "str.h"
#include "real.h"
#include "int.h"

#define GLOBAL 0
#define LOCAL 1

/*** HELPER FUNCTION DECLARATIONS ***/
//none

int main(void){

//case: initializing the environment
    printf("Creating global environment...\n");
    lexeme_t *env = newEnv();
    if(env) printf("Global envirnment created!\n");

//case: creating a global variable
    lexeme_t *var = newLexeme("x");
    lexeme_t *val = newLexeme("3");
    printf("Inserting variable x with a value of 3...\n");
    insert(var, val, env);
    printf("Insertion complete!\n");

//case: show the global environment
    print_env(stdout, env, LOCAL);

//case: creating a local environment
    printf("\nExtending the environment...\n");
    var = newLexeme("y");
    val = newLexeme("5");
    lexeme_t *env1 = extend(var, val, env);
    printf("Extension complete!\n");

//case: inserting into the local environemnt
    printf("Inserting variable y with a value of 5...\n");
    insert(var, val, env1);
    printf("Insertion complete!\n");

//case: show the environment
    print_env(stdout, env1, LOCAL);

//case: looking up a local variable from local scope
    printf("\nLooking up variable y in the local environment...\n");
    lexeme_t *y = lookup(newLexeme("y"), env1);
    printf("Success! variable y = ");
    printLexeme(stdout, y);
    printf("\n");

//case: looking up the global variable from local scope
    var = newLexeme("x");
    printf("Looking up global variable x from the local environment...\n");
    lexeme_t *x = lookup(var, env1);
    printf("Variable x = ");
    printLexeme(stdout, x);
    printf("\n");

//case: creating another local environment, not accessible from the first
    printf("Extending the global environment...\n");
    lexeme_t *env2 = extend(newLexeme("non"), newLexeme(NULL), env);
    printf("Extension complete!\n");

//case: updating the global variable from the new local scope
    printf("Updating x...\n");
    update(newLexeme("x"), newLexeme("10"), env2);
    printf("Update complete! x = ");
    printLexeme(stdout, lookup(newLexeme("x"), env2));
    printf("\n");

//case: show the environment
    print_env(stdout, env2, GLOBAL);

//case: inserting a variable into an environment with a pre-existing variable
    printf("\nInserting variable z into first local environment...\n");
    insert(newLexeme("z"), newLexeme(NULL), env1);
    printf("Insert complete!\n");

//case: show the environment
    print_env(stdout, env1, LOCAL);

//case: updating the new variable
    printf("\nUpdating variable z with value 6...\n");
    update(newLexeme("z"), newLexeme("6"), env1);
    printf("Update complete! Variable z = ");
    printLexeme(stdout, lookup(newLexeme("z"), env1));
    printf("\n");

//case: show the environment
    print_env(stdout, env1, GLOBAL);

//case: looking up a variable out of scope
    printf("\nLooking up variable y from outside scope...\n");
    y = lookup(newLexeme("y"), env2); //should fail
    printf("Variable y = ");
    printLexeme(stdout, y);
    printf("\n");

//test complete
    printf("Test complete! (in error!)\n");

    return 0;

}
