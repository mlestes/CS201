#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gt.h"
#include "rbt.h"
#include "str.h"
#include "scanner.h"
#include "corpus.h"

/*****************************************************************************/
/* trees BY Murray Estes                                                     */
/* PURPOSE: To implement a program to compare the performance of green trees */
/*          and red-black trees.                                             */
/*****************************************************************************/

/*** CONSTANTS ***/
#define GTREE 2
#define RBTREE 1
#define NOTREE 0
#define INPUT 0
#define COMMAND 1
#define OUTPUT 2
#define TRUE 1
#define FALSE 0
#define EQUAL 0

/*** SUPPORTING FUNCTION DECLARATIONS ***/
static string *readFile(FILE *);
static int getOption(char **);
static FILE **getFiles(int, char**);
static GT *buildGT(FILE *);
static RBT *buildRBT(FILE *);
static void commandGT(FILE *, FILE *, GT *);
static void commandRBT(FILE *, FILE *, RBT *);

/*** MAIN FUNCTION ***/
int main(int argc, char **argv){

    int treeOpt = getOption(argv);
    if(treeOpt == NOTREE){
        printf("Murray L.Estes\n");
        exit(0);
        }
    FILE **fileOpts = getFiles(argc, argv);
    if(treeOpt == GTREE){
        GT *gtree = buildGT(fileOpts[INPUT]);
        commandGT(fileOpts[COMMAND], fileOpts[OUTPUT], gtree);
        }
    else if(treeOpt == RBTREE){
        RBT *rtree = buildRBT(fileOpts[INPUT]);
        commandRBT(fileOpts[COMMAND], fileOpts[OUTPUT], rtree);
        }

    return 0;

    }

/*** SUPPORTING FUNCTION DEFINITIONS ***/
int getOption(char **argv){

    if(strcmp(argv[1], "-g") == 0) return GTREE;
    else if(strcmp(argv[1], "-v") == 0) return NOTREE;
    else return RBTREE;

    }

string *readFile(FILE *fp){

    char *thing;
    if(stringPending(fp)) thing = readString(fp);
    else thing = readToken(fp);
    if(thing != 0) thing = cleanText(thing);
    if(thing == 0) return 0;
    else return newString(thing);

    }

FILE **getFiles(int c, char **v){

    FILE **files = malloc(sizeof(FILE *) * 3);
    assert(files != 0);
    int j = 0;
    for(int i = 1; i < 5; i++){
        if(j == 0 && i == 1 && 
          (strcmp(v[i], "-r") == 0 || strcmp(v[i], "-g") == 0))
            continue;
        else{
            if(j != OUTPUT){
                files[j++] = fopen(v[i], "r");
                if(files[j - 1] == 0){
                    fprintf(stderr, "Error: Failed to open \"%s\".\n",v[i]);
                    exit(1);
                    }
                }
            else{
                if(i < c){
                    files[j] = fopen(v[i], "a");
                    if(files[j - 1] == 0){
                        fprintf(stderr, "Error: Failed to open %s.\n",v[i]);
                        exit(1);
                        }
                    }
                else files[j] = stdout;
                break;
                }
            }
        }

    return files;

    }

GT *buildGT(FILE *fp){
    GT *tree = newGT(printString, compareString);
    string *in = readFile(fp);
    while(feof(fp) == FALSE){ //read in corpus
        if(in != 0) insertGT(tree, in);
        in = readFile(fp);
        }

    return tree;

    }

RBT *buildRBT(FILE *fp){
    
    RBT *tree = newRBT(printString, compareString);
    string *in = readFile(fp);
    while(feof(fp) == FALSE){
        if(in != 0) insertRBT(tree, in);
        in = readFile(fp);
        }
    
    return tree;

    }

void commandGT(FILE *input, FILE *out, GT *tree){

    string *in = readFile(input);
    while(feof(input) == FALSE){ 
        if(compareString(in, newString("i")) == EQUAL){
            in = readFile(input);
            if(in != 0) insertGT(tree, in);
            }
        else if(compareString(in, newString("d")) == EQUAL){
            in = readFile(input);
            deleteGT(tree, in);
            }
        else if(compareString(in, newString("s")) == EQUAL)
            displayGT(out, tree);
        else if(compareString(in, newString("f")) == EQUAL){
            in = readFile(input);
            fprintf(out, "Frequency of %s: %d\n", 
                    getString(in), findGT(tree, in));
            }
        else if(compareString(in, newString("r")) == EQUAL)
            statisticsGT(out, tree);
        in = readFile(input);
        }

    }

void commandRBT(FILE *input, FILE *out, RBT *tree){

    string *in = readFile(input);
    while(feof(input) == FALSE){ //read in commands
        if(compareString(in, newString("i")) == EQUAL){
            in = readFile(input);
            if(in != 0) insertRBT(tree, in);
            }
        else if(compareString(in, newString("d")) == EQUAL){
            in = readFile(input);
            deleteRBT(tree, in);
            }
        else if(compareString(in, newString("s")) == EQUAL)
            displayRBT(out, tree);
        else if(compareString(in, newString("f")) == EQUAL){
            in = readFile(input);
            fprintf(out, "Frequency of %s: %d\n", 
                    getString(in), findRBT(tree,in));
            }
        else if(compareString(in, newString("r")) == EQUAL)
            statisticsRBT(out, tree);
        in = readFile(input);
        }

    }
