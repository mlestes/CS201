/*****************************************************************************/
// lexer.c by Murray Estes
// A lexing function for a custom programming language.
// Begin date: 20190119
// Complete date:
/*****************************************************************************/
// Usage:
// lexeme_t *lex(FILE *fp); Analyzes a portion of a file and returns a lexeme
//                          object.
//     lexeme_t *l = lex(fp);
//
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "lexeme.h"

#define ERR_0 "Invalid number string."
#define ERR_1 "Unknown token type."
#define ERR_2 "Invalid string. Expected '\"' missing."

extern int line;

/*** PRIVATE FUNCTION DECLARATIONS ***/
void skipwhitespace(FILE *);
lexeme_t *lexString(FILE *);
lexeme_t *lexNum(FILE *);
lexeme_t *lexWord(FILE *);
lexeme_t *lexError(FILE *, char *);
lexeme_t *parseError(char *, FILE *, char *);
char *grow(char *, int *);

/*** MAIN/PUBLIC FUNCTION DEFINITIONS ***/
lexeme_t *lex(FILE *fp){

    skipwhitespace(fp);
    char c;
    c = fgetc(fp);
    if(c == EOF){
        lexeme_t *l = newLexeme("END_OF_FILE");
        setLexemeType(END_READ, l);
        return l;
    }
    switch(c){
        case '(': return newLexeme("(");
        case ')': return newLexeme(")");
        case ';': return newLexeme(";");
        case ':': return newLexeme(":");
        case '.': return newLexeme(".");
        case '+':
            c = fgetc(fp);
            if(c == '+'){
                //ungetc(c, fp);
                return newLexeme("++");
            }
            else{
                ungetc(c, fp);
                return newLexeme("+");
            }
        case '-':
            c = fgetc(fp);
            if(c == '-'){
                //ungetc(c, fp);
                return newLexeme("--");
            }
            else{
                ungetc(c, fp);
                return newLexeme("-");
            }
        case '*':
            c = fgetc(fp);
            if(isspace(c)){
                ungetc(c, fp);
                return newLexeme("*");
            }
            else{
                ungetc(c, fp);
                return newLexeme("STAR");
            }
        case '/': return newLexeme("/");
        case '\"': return lexString(fp);
        case '<':
            c = fgetc(fp);
            if(c == '=') return newLexeme("<=");
            else{
                ungetc(c, fp);
                return newLexeme("<");
            }
        case '>':
            c = fgetc(fp);
            if(c == '=') return newLexeme(">=");
            else{
                ungetc(c, fp);
                return newLexeme(">");
            }
        case '!': return newLexeme("!");
        case '%': return newLexeme("%");
        case '^': return newLexeme("^");
        case '=':
            c = fgetc(fp);
            if(c == '=') return newLexeme("==");
	    else{
                ungetc(c, fp);
                return newLexeme("=");
            }
        case '?': return newLexeme("?");
        case '&': return newLexeme("&");
        default:
            if(isdigit(c)){
                ungetc(c, fp);
                return lexNum(fp);
            }
            else if(isalpha(c)){
                ungetc(c, fp);
                return lexWord(fp);
            }
            else{
                ungetc(c, fp);
                return lexError(fp, ERR_1);
            }
    }
}

/*** PRIVATE FUNCTION DEFINITIONS ***/
void skipwhitespace(FILE *fp){

    char c, d;
    c = fgetc(fp);
    if(c == '/'){
        d = fgetc(fp);
	if(d == '/'){
            c = fgetc(fp);
	    while(c != '\n') c = fgetc(fp);
	}
	else if(d == '*'){
            comment:
	    while(c != '*'){
	        if(c == '\n') line++;
		c = fgetc(fp);
	    }
	    c = fgetc(fp);
	    if(c != '/') goto comment;
	    else c = fgetc(fp);
	}
	else{
            ungetc(d, fp);
	    ungetc(c, fp);
	}
    }
    else if(isspace(c)){
        while(isspace(c)){
            if(c == '\n') line++;
	    c = fgetc(fp);
	}
    }

    if(c == '/'){
        d = fgetc(fp);
	if(d == '/' || d == '*'){
            ungetc(d, fp);
	    ungetc(c, fp);
	    skipwhitespace(fp);
	}
        else{
            ungetc(d, fp);
	    ungetc(c, fp);
	}
    }
    else if(isspace(c)){
        ungetc(c, fp);
	skipwhitespace(fp);
    }
    else ungetc(c, fp);

}

lexeme_t *lexString(FILE *fp){

    int size = 1;
    char *str = malloc(sizeof(char));
    int i = 0;
    char c = fgetc(fp);
    while(c != '\"'){
        if(c == EOF){
            ungetc(c, fp);
            return parseError(str, fp, ERR_2);
        }
        str[i] = c;
	i++;
	if(i >= size) str = grow(str, &size);
        c = fgetc(fp);
    }

    str[i] = '\0';
    lexeme_t *l = newLexeme(str);
    setLexemeType(STRING_, l);
    return l;

}

lexeme_t *lexNum(FILE *fp){

    int size = 1;
    int hasdot = 0; int isnegative = 0;
    char *str = malloc(sizeof(char));
    int i = 0;
    char c = fgetc(fp);
    while(!feof(fp) && (isdigit(c) || c == '.' || c == '-')) {
        if(c == '-'){
            if(i == 0 && isnegative == 0){
                isnegative = 1;
	        str[i++] = c;
            }
            else{
                ungetc(c, fp);
                return parseError(str, fp, ERR_0);
            }
        }
        else if(c == '.'){
            if(hasdot == 0){
                hasdot = 1;
		str[i++] = c;
            }
            else{
                ungetc(c, fp);
                return parseError(str, fp, ERR_0);
            }
        }
        else str[i++] = c;
        if(i >= size) str = grow(str, &size);
	c = fgetc(fp);
    }

    ungetc(c, fp);
    str[i] = '\0';
    return newLexeme(str);

}

lexeme_t *lexWord(FILE *fp){

    int size = 1;
    char *str = malloc(sizeof(char));
    int i = 0;
    char c = fgetc(fp);
    while(isalpha(c) || isdigit(c)){
        str[i++] = c;
	if(i >= size) str = grow(str, &size);
        c = fgetc(fp);
    }
    
    ungetc(c, fp);
    str[i] = '\0';
    lexeme_t *l = newLexeme(str);
    if(strcmp(getLexemeType(l), STRING_) == 0) setLexemeType(VARIABLE, l);
    return l;

}

lexeme_t *lexError(FILE *fp, char *err){

    int size = 1;
    char *str = malloc(sizeof(char));
    int i = 0;
    char c = fgetc(fp);
    while(!isspace(c)){
        str[i++] = c;
	if(i >= size) str = grow(str, &size);
        c = fgetc(fp);
    }
    
    str[i] = '\0';
    lexeme_t *l = newLexeme(str);
    setLexemeType(ERROR, l);
    setLexemeError(err, l);

    ungetc(c, fp);
    return l;

}

lexeme_t *parseError(char *str, FILE *fp, char *err){

    int size = strlen(str);
    while(size > 0) ungetc(str[--size], fp);
    return lexError(fp, err);

}

char *grow(char *str, int *size){

    *size *= 2;
    str = realloc(str, sizeof(char) * *size);
    return str;

}
