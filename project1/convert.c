#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "queue.h"
#include "stack.h"
#include "bst.h"
#include "str.h"
#include "real.h"
#include "value.h"

/*****************************************************************************/
/* convert.c BY Muray Estes                                                  */
/* PURPOSE: To implement a postfix to infix converter using the              */
/*          Shunting-Yard algorith.                                          */
/* METHOD DESCRIPTIONS:                                                      */
/*     queue *convert(queue *input, bst *var);                               */
/*         Returns an output queue that is the converted form of the given   */
/*         input queue. The binary search tree contains any declared         */
/*         variables and is only included to ensure that only declared       */
/*         variables are included in the conversion.                         */
/*                                                                           */
/*     double evaluate(queue *q, bst *var);                                  */
/*         Returns the result of the given input queue.                      */
/*                                                                           */
/*****************************************************************************/

#define REAL 2
#define STRING 3

/*** PRIVATE FUNCTIONS ***/
static int isOperator(string *);
static int isNumber(string *);
static int isVariable(string *, BST *);
static int setPrecedence(string *);
static int comparePrecedence(string *, string *);
static double compute(real *, real *, string *);

/*** PUBLIC METHODS ***/
QUEUE *convert(QUEUE *input, BST *var){

    QUEUE *output = newQUEUE(printString);
    STACK *op = newSTACK(printString);
    while(sizeQUEUE(input) > 0){
        string *item = dequeue(input);
        if(isNumber(item)) enqueue(output, item);
        else if(isOperator(item)){
            if(sizeSTACK(op) > 0){
                string *test = peekSTACK(op);
                while(comparePrecedence(item, test) <= 0){
                    string *hiop = pop(op);
                    enqueue(output, hiop);
                    if(sizeSTACK(op) > 0) test = peekSTACK(op);
                    else break;
                    }
                }
            push(op, item);
            }
        else if(compareString(item, newString("(")) == 0) push(op, item);
        else if(compareString(item, newString(")")) == 0){
            while(compareString(peekSTACK(op), newString("("))){
                string *poop = pop(op);
                enqueue(output, poop);
                }
            pop(op);
            }
        else if(isVariable(item, var)) enqueue(output, item);
        else if(compareString(item, newString(";")) != 0){
            fprintf(stdout, "variable %s was not declared\n", getString(item));
            exit(0);
            }
        }
    while(sizeSTACK(op) > 0){
        string *xop = pop(op);
        enqueue(output, xop);
        }

    return output;

    }

double evaluate(QUEUE *q){
    /*
    double result = 0; int vardec = 0;
    QUEUE *que = newQUEUE(printString);
    string *a = dequeue(q);
    string *b = dequeue(q);
    string *op = dequeue(q);
    while(!isOperator(op)){
        enqueue(que, a);
        a = b;
        b = op;
        op = dequeue(q);
        }
    if(!isNumber(a)){
        char *varName = getString(a);
        a = findBST(var, a);
        if(!a){
            if(!vardec){
                fprintf(stdout, "variable %s was not declared\n", varName);
                exit(0);
                }
            else a = newString(varName);
            }
        }
    if(!isNumber(b)){
        char *varName = getString(b);
        b = findBST(var, b);
        if(!b){
            fprintf(stdout, "variable %s was not declared\n", varName);
            exit(0);
            }
        }
    result = compute(a, b, op, var);
    char *r = malloc(sizeof(result)/sizeof(char));
    snprintf(r, sizeof(result)/sizeof(char), "%f", result);
    enqueue(que, newString(r));
    while(sizeQUEUE(q) > 0){
        string *thing = dequeue(q);
        enqueue(que, thing);
        }
    if(sizeQUEUE(que) > 1) result = evaluate(que, var);
    */

    double result = 0;
    QUEUE *out = newQUEUE(printReal);
    value *a = dequeue(q);
    value *b = dequeue(q);
    value *op = dequeue(q);
    while(getValueType(op) != STRING){
        enqueue(out, a);
        a = b;
        b = op;
        op = dequeue(q);
        }
    real *x = getValue(a);
    real *y = getValue(b);
    string *o = getValue(op);
    result = compute(x, y, o);
    enqueue(out, newValue(newReal(result), REAL, printReal));
    while(sizeQUEUE(q) > 0) enqueue(out, dequeue(q));
    if(sizeQUEUE(out) > 1) result = evaluate(out);

    return result;

    }

/*** PRIVATE FUNCTIONS ***/
int isOperator(string *str){

    int isit = 0;
    string *test = newString("^");
    if(compareString(str, test) == 0) isit = 1; setString(test, "%");
    if(compareString(str, test) == 0) isit = 1; setString(test, "/");
    if(compareString(str, test) == 0) isit = 1; setString(test, "*");
    if(compareString(str, test) == 0) isit = 1; setString(test, "-");
    if(compareString(str, test) == 0) isit = 1; setString(test, "+");
    if(compareString(str, test) == 0) isit = 1;

    return isit;

    }

int setPrecedence(string *str){

    int prec = 0;
    string *test = newString("^");
    if(getString(str)){
        if(compareString(str, test) == 0) prec = 7; setString(test, "%");
        if(compareString(str, test) == 0) prec = 6; setString(test, "/");
        if(compareString(str, test) == 0) prec = 5; setString(test, "*");
        if(compareString(str, test) == 0) prec = 4; setString(test, "-");
        if(compareString(str, test) == 0) prec = 3; setString(test, "+");
        if(compareString(str, test) == 0) prec = 2;
        }

    return prec;

    }

int comparePrecedence(string *a, string *b){

    int aPrec = setPrecedence(a);
    int bPrec = setPrecedence(b);

    return aPrec - bPrec;

    }

double compute(real *a, real *b, string *op){
    
    double result = 0;
    double x = getReal(a);
    double y = getReal(b);
    char *operator = getString(op);
    if(strcmp(operator, "^") == 0) result = pow(x, y);
    else if(strcmp(operator, "%") == 0) result = fmod(x, y);
    else if(strcmp(operator, "/") == 0) result = x / y;
    else if(strcmp(operator, "*") == 0) result = x * y;
    else if(strcmp(operator, "-") == 0) result = x - y;
    else if(strcmp(operator, "+") == 0) result = x + y;

    return result;

    }

int isNumber(string *str){

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

int isVariable(string *str, BST *var){

    int isit = 0;
    if(findBST(var, str)) isit = 1;

    return isit;

    }
