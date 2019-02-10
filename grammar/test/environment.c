/*****************************************************************************/
// environment.c by Murray Estes
// A program to test the environment implementation for ESL
// Begin Date: 20190207
// Complete Date:
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../type/type.h"
#include "../lex/lexeme.h"
#include "../env/env.h"

#define GLOBAL 0
#define LOCAL 1

/*** HELPER FUNCTION DECLARATIONS ***/
//none

int main(void){

//case: initializing the environment
    printf("Creating global environment...\n");
    lexeme_t *env = newEnv();
    if(env) printf("Global environment created!\n");

//case: creating a global variable
    printf("Inserting variable x with a value of 3...\n");
    insert(newLexeme("x"), newLexeme("3"), env);
    printf("Insertion complete!\n");
    print_env(stdout, env, GLOBAL);

//case: creating a local environment
    printf("Extending the environment...\n");
    lexeme_t *env1 = extend(newLexeme("y"), newLexeme("5"), env);
    printf("Extension complete!\n");

//case: inserting into the local environemnt
    printf("Inserting variable y with a value of 5...\n");
    insert(newLexeme("y"), newLexeme("5"), env1);
    print_env(stdout, env1, LOCAL);

//case: looking up a local variable from local scope
    printf("Looking up variable y in the local environment...\n");
    lexeme_t *y = lookup(newLexeme("y"), env1);
    printf("Success! variable y = ");
    printLexeme(stdout, y);
    printf("\n");

//case: looking up the global variable from local scope
    printf("Looking up global variable x from the local environment...\n");
    lexeme_t *x = lookup(newLexeme("x"), env1);
    printf("Variable x = ");
    printLexeme(stdout, x);
    printf("\n");
    print_env(stdout, env1, GLOBAL);

//case: creating another local environment, not accessible from the first
    printf("Extending the global environment...\n");
    lexeme_t *env2 = extend(newLexeme(NULL), newLexeme(NULL), env);
    printf("Extension complete!\n");

//case: updating the global variable from the new local scope
    printf("Updating x...\n");
    update(newLexeme("x"), newLexeme("10"), env2);
    printf("Update complete! x = ");
    printLexeme(stdout, lookup(newLexeme("x"), env2));
    printf("\n");
    print_env(stdout, env2, GLOBAL);

//case: inserting a variable into an environment with a pre-existing variable
    printf("Inserting variable z into first local environment...\n");
    insert(newLexeme("z"), newLexeme(NULL), env1);
    printf("Insert complete!\n");
    print_env(stdout, env1, LOCAL);

//case: updating the new variable
    printf("Updating variable z with value 6...\n");
    lexeme_t *z = update(newLexeme("z"), newLexeme("6"), env1);
    printf("Update complete! Variable z = ");
    printLexeme(stdout, z);
    printf("\n");
    print_env(stdout, env1, GLOBAL);

//case: looking up a variable out of scope
    printf("Looking up variable y from outside scope...\n");
    y = lookup(newLexeme("y"), env2); //should fail
    printf("Variable y = ");
    printLexeme(stdout, y);
    printf("\n");

//test complete
    printf("Test complete! (in error!)\n");


}
