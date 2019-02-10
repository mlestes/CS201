/*****************************************************************************/
// scanner.c by Murray Estes
// A scanner file iso parsing source code of a custom programming language.
// Begin Date: 20190121
// Complete Date:
/*****************************************************************************/
// Usage (Command line)
// scanner <file name>
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lex/lexeme.h"
#include "../lex/lexer.h"
#include "../type/type.h"

/*** PRIVATE FUNCTION DECLARATIONS ***/
//none

/*** MAIN/PUBLIC FUNCTION DEFINITITIONS ***/
int main(int argc, char **argv){

    //check for correct number of inputs
    if(argc < 2){ //too few inputs
        fprintf(stderr, "Error: incorrect number of inputs.\n"
                        "Usage: scanner <file>\n");
	exit(-1);
    }

    //attempt to open the file
    FILE *fp = fopen(argv[1], "r");
    if(!fp){ //attempt failed
        fprintf(stderr, "Error: could not open file \"%s\"\n", argv[1]);
	exit(-1);
    }

    //scan the source code, printing each lexeme
    while(!feof(fp)){
        lexeme_t *lexeme = lex(fp);
        printLexeme(stdout, lexeme);
        fprintf(stdout, "\n");
	char *type = getLexemeType(lexeme);
	if(strcmp(type, ERROR) == 0) exit(-1);
	if(strcmp(type, END_READ) == 0) break;

    }

    return 0;

}

/*** PRIVATE FUNCTION DEFINITIONS ***/
//none
