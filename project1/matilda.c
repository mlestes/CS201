#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "scanner.h"
#include "stack.h"
#include "queue.h"
#include "bst.h"
#include "str.h"
#include "real.h"
#include "value.h"
#include "convert.h"

#define REAL 2
#define STRING 3

/*** SUPPORTING FUNCTION SIGNATURES ***/
static QUEUE *readFile(FILE *);
static void displayPair(FILE *, void *, void *);
static void printQueue(QUEUE *);
static int *getOptions(int, char **);
static void prepQueue(QUEUE *, BST *);
static int isDouble(string *);
static int isOperator(string *);

/*** MAIN FUNCTION ***/
int main(int argc, char **argv){

    //opts[0] = -v opts[1] = -i opts[2] = -p opts[3] = -b
    int *opts = getOptions(argc, argv);
    if(opts[0]) printf("Murray L. Estes\n");
    else{
        FILE *fp = fopen(argv[argc - 1], "r");
        QUEUE *input = newQUEUE(printString);
        QUEUE *output = newQUEUE(printString);
        assert(fp != 0);
        double result = 0;
        BST *var = newBST(displayPair, compareString);
        while(fp){
            input = readFile(fp);
            if(feof(fp)) break;
            if(opts[1]){printQueue(input); printf("\n");}
            if(compareString(peekQUEUE(input), newString("var")) == 0){
                dequeue(input);
                string *key = dequeue(input);
                dequeue(input);
                string *value = dequeue(input);
                real *val = newReal(atof(getString(value)));
                insertBST(var, key, val);
                continue;
                }
            output = convert(input, var);
            }
        if(opts[2]){printQueue(output); printf("\n");}
        prepQueue(output, var);
        if(opts[3]){displayBST(stdout, var); printf("\n");}
        result = evaluate(output);
        printf("%f\n",result);
        }

    return 0;

    }

/*** SUPPORTING FUNCTIONS ***/
QUEUE *readFile(FILE *fp){

    char *input = 0;
    QUEUE *q = newQUEUE(printString);
    while(fp){
        if(stringPending(fp)) input = readString(fp);
        else input = readToken(fp);
        if(feof(fp)) break;
        string *thing = newString(input);
        enqueue(q, thing);
        if(strcmp(input, ";") == 0) break;
        }

    return q;

    }

void displayPair(FILE *fp, void *a, void *b){

    string *alpha = (string *) a;
    real *beta = (real *) b;
    printString(fp, alpha);
    fprintf(fp, "=");
    printReal(fp, beta);

    }

void printQueue(QUEUE *q){

    int size = sizeQUEUE(q);
    for(int i = 0; i < size; i++){
        string *thing = dequeue(q);
        enqueue(q, thing);
        printString(stdout,thing);
        if(i < size - 1)printf(" ");
        }

    }

int *getOptions(int argc, char **argv){
    int *opts = malloc(sizeof(int) * 4);
    assert(opts != 0);
    for(int i = 0; i < 4; i++) opts[i] = 0;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-v") == 0) opts[0] = 1; //print author name
        else if(strcmp(argv[i], "-i") == 0) opts[1] = 1; //print original in
        else if(strcmp(argv[i], "-p") == 0) opts[2] = 1; //print last out
        else if(strcmp(argv[i], "-b") == 0) opts[3] = 1; //print bst
        }

    return opts;

    }

void prepQueue(QUEUE *q, BST *var){

    int size = sizeQUEUE(q);
    for(int i = 0; i < size; i++){
        string *item = dequeue(q);
        char *it = getString(item);
        if(isDouble(item))
            enqueue(q, newValue(newReal(atof(it)), REAL, printReal));
        else if(isOperator(item)){
            enqueue(q, newValue(item, STRING, printString));
            }
        else{
            item = findBST(var, item);
            if(item){
                value *v = newValue(item, REAL, printReal);
                enqueue(q, v);
                }
            else{
                fprintf(stdout, "variable %s not declared\n", it);
                exit(0);
                }
            }
        }

    }

int isDouble(string *str){

    int isit = 0;
    char *s = getString(str);
    int size = sizeString(str);
    for(int i = 0; i < size; i++){
        if(s[i] >= 48 && s[i] <= 57) isit = 1;
        else if(s[i] == 46 && size > 1) isit = 1;
        else if(s[0] == 45 && size > 1) isit = 1;
        else{
            isit = 0;
            break;
            }
        }

    return isit;

    }

int isOperator(string *str){

    int isit = 0;
    if(compareString(str, newString("^")) == 0) isit = 1;
    else if(compareString(str, newString("%")) == 0) isit = 1;
    else if(compareString(str, newString("/")) == 0) isit = 1;
    else if(compareString(str, newString("*")) == 0) isit = 1;
    else if(compareString(str, newString("-")) == 0) isit = 1;
    else if(compareString(str, newString("+")) == 0) isit = 1;

    return isit;

    }
