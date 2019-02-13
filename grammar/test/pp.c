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
#include "../env/env.h"
#include "../parse/parse.h"
#include "../lex/lexeme.h"
#include "../lex/lexer.h"
#include "../type/type.h"

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
void print_tree(lexeme_t *, int);

/*** MAIN/PUBLIC FUNCTION DEFINITITIONS ***/
int main(int argc, char **argv){

    glb_init(argc, argv);

    //read the source code, stopping at either EOF or error
    lexeme_t *tree = program();
    match(END_READ);
    print_tree(tree, 0);
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
    FILE *fp = fopen(argv[1], "r");
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

void print_tree(lexeme_t *tree, int level){

    if(!tree) return;
    int i;
    int type = getLexemeType(tree);
    switch(type){
        case IF:
        for(i = 0; i < level; i++) printf("    "); 
        printf("IF\n");
        break;
        case ELSE:
        for(i = 0; i < level; i++) printf("    "); 
        printf("ELSE\n");
        break;
        case BLOCK:
        for(i = 0; i < level; i++) printf("    "); 
        printf("BEGIN\n");
        level++;
        break;
        case DEFINE:
        for(i = 0; i < level; i++) printf("    "); 
        printf("DEFINE\n");
        break;
        case STRUCT:
        for(i = 0; i < level; i++) printf("    "); 
        printf("STRUCT\n");
        break;
        case VAR:
        for(i = 0; i < level; i++) printf("    ");
        printf("VAR\n");
        break;
        case WHILE:
        for(i = 0; i < level; i++) printf("    ");
        printf("WHILE\n");
        break;
    }
    if(getLexemeLeft(tree)) print_tree(getLexemeLeft(tree), level);
    if(getLexemeRight(tree)) print_tree(getLexemeRight(tree), level);
    if(getLexemeValue(tree)) {
        for(i = 0; i < level; i++) printf("    ");
        printLexeme(stdout, tree);
        printf("\n");
    }
    if(type == BLOCK){
        level--;
        for(i = 0; i < level; i++) printf("    ");
        printf("END\n\n");
    }
}