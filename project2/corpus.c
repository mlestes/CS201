#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//LOCAL INCLUDES
#include "corpus.h"

/*****************************************************************************/
/* corpus.c BY Murray Estes                                                  */
/* PUPRPOSE: To implement a text parser for viewing a corpus of text.        */
/* METHOD DESCRIPTIONS:                                                      */
/*     char *cleanText(char *str);                                           */
/*         Cleans the given string to comply with specified requirements.    */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0

/*** STRUCTS ***/
//none

/*** PRIVATE FUNCTION DECLARATIONS ***/
static int isSpace(char);
static int isUpper(char);
static char toLower(char);
static int isLower(char);

/*** PUBLIC FUNCTION DEFINITIONS ***/
char *cleanText(char *str){

    int i, j;
    int size = strlen(str) + 1;
    j = 0;
    int space = FALSE;
    for(i = 0; i < size; i++){
        if(j > 0 && space == FALSE && isSpace(str[i]) == TRUE){
            space = TRUE;
            str[j++] = ' ';
            continue;
            }
        else if(isUpper(str[i]) == TRUE){
            space = FALSE;
            str[j++] = toLower(str[i]);
            continue;
            }
        else if(isLower(str[i]) == TRUE){
            space = FALSE;
            str[j++] = str[i];
            continue;
            }
        }
    if(str[j - 1] == ' ') str[j - 1] = '\0';
    else str[j] = '\0';
    if(j == 0) return 0;
    else return str;

    }

/*** PRIVATE FUNCTION DEFINITIONS ***/
int isSpace(char c){

    if(c == ' ' || c == '\t' || c == '\n') return TRUE;
    else return FALSE;

    }

int isUpper(char c){

    if(c >= 'A' && c <= 'Z') return TRUE;
    else return FALSE;

    }

int isLower(char c){

    if(c >= 'a' && c <= 'z') return TRUE;
    else return FALSE;

    }

char toLower(char c){

    if(isUpper(c)) return c + 32;
    else return c;

    }
