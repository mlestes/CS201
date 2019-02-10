/*****************************************************************************/
// pp.c by Murray Estes
// A pretty printer iso parsing source code of ESL.
// Begin Date: 20190209
// Complete Date:
/*****************************************************************************/
// Usage (Command line)
// pp <file name>
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "env.h"
#include "parse.h"
#include "lexeme.h"
#include "lexer.h"
#include "type.h"
#include "str.h"

#define TRUE 1
#define FALSE 0

/*** GLOBALS ***/
FILE *fp;
lexeme_t *current;
lexeme_t *env;
int line = 1;

/*** PRIVATE FUNCTION DECLARATIONS ***/
FILE *file_init(int, char **);
void glb_init(int, char **);

/*** MAIN/PUBLIC FUNCTION DEFINITITIONS ***/
int main(int argc, char **argv){

    glb_init(argc, argv);

    //read the source code, stopping at either EOF or error
    program();
    match(END_READ);
    fprintf(stdout, "Parse complete. No errors.\n");
    fclose(fp);

    return 0;

}

/*** PRIVATE FUNCTION DEFINITIONS ***/
FILE *file_init(int argc, char **argv){

    //check for correct number of inputs
    if(argc < 2){ //too few inputs
        fprintf(stderr, "Error: incorrect number of inputs.\n"
                        "Usage: ./pp <file>\n");
	exit(-1);
    }

    //attempt to open the file
    fp = fopen(argv[1], "r");
    if(!fp){ //attempt failed
        fprintf(stderr, "Error: could not open file \"%s\".\n"
			"File either missing or spelled incorrectly.\n", 
			argv[1]);
	exit(-1);
    }

    //check if file extension is .esl
    int len = strlen(argv[1]) - 1;
    char *name = argv[1];
    if(name[len-3] != '.' || name[len-2] != 'e' || name[len-1] != 's' || 
       name[len] != 'l'){
        fprintf(stderr, "Error: unrecognized file type. File must be of "
			"extension \".esl\"\n");
	exit(-1);
    }

    return fp;
    
}

void glb_init(int argc, char **argv){

    fp = file_init(argc, argv);
    env = newEnv();
    current = lex(fp);

}