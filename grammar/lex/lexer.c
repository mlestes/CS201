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
#include <ctype.h>
#include "lexer.h"
#include "lexeme.h"

#define ERR_0 "Invalid number string.\n"
#define ERR_1 "Unknown token type.\n"
#define ERR_2 "Invalid string. Expected '\"' missing.\n"

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

    char c;
    skipwhitespace(fp);
    c = fgetc(fp);
    switch(c){
        case '(': return newLexeme("(");
        case ')': return newLexeme(")");
        case ';': return newLexeme(";");
        case ':': return newLexeme(":");
        case '.': return newLexeme(".");
        case '+':
            c = fgetc(fp);
            if(c == '+') return newLexeme("++");
            else{
                ungetc(c, fp);
                return newLexeme("+");
            }
        case '-':
            c = fgetc(fp);
            if(c == '-') return newLexeme("--");
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

    char c = fgetc(fp);
    //skip the whitespace
    while(isspace(c)) c = fgetc(fp);

    //skip comments
    if(c == '/'){
        c == fgetc(fp);
        //single line comment
        if(c == '/'){
            while(c != '\n') c = fgetc(fp);
        }
        //multi-line comment
        else if(c == '*'){
            comment_loop:
            while(c != '*') c = fgetc(fp);
            c = fgetc(fp);
            if(c != '/') goto comment_loop;
        }
	//not a comment at all
        else ungetc(c, fp);
    }

    //make sure there isn't more space
    c = fgetc(fp);
    if(isspace(c)) skipwhitespace(fp);

    //make sure there isn't more comments
    else if(c == '/'){
	char d = fgetc(fp);
	if(d == '*' || d == '/'){
            //push back the initial comment start chars
	    ungetc(d, fp);
            ungetc(c, fp);
            skipwhitespace(fp);
	}
	else{
            //not a comment, still push back the chars
            ungetc(d, fp);
            ungetc(c, fp);
        }
    }

    //push back the char that got us out of this
    else ungetc(c, fp);

}

lexeme_t *lexString(FILE *fp){

    int size = 1;
    char *str = malloc(sizeof(char));
    int i = 0;
    c = fgetc(fp);
    while(c != '\"'){
        if(c == 'EOF') return parseError(str, fp, ERR_2);
        str[i] = c;
	i++;
	if(i >= size) str = grow(str, &size);
        c = fgetc(fp);
    }

    return newLexeme(str);

}

lexeme_t *lexNum(FILE *fp){

    int size = 1;
    int hasdot = 0; int isnegative = 0;
    char *str = malloc(sizeof(char));
    int i = 0;
    c = fgetc(fp);
    while(!isspace(c)){
        if(c == '-'){
            if(i == 0 && isnegative == 0){
                isnegative = 1;
	        str[i++] = c;
            }
            else return parseError(str, fp, ERR_0);
        }
        else if(c == '.'){
            if(hasdot == 0){
                hasdot = 1;
		str[i++] = c;
            }
            else return parseError(str, fp, ERR_0);
        }
	else if(!isdigit(c)) return parseError(str, fp, ERR_0);
        else str[i++] = c;
        if(i >= size) str = grow(str, &size);
	c = fgetc(fp);
    }

    ungetc(c, fp);
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
    return newLexeme(str);

}

lexme_t *lexError(FILE *fp, char *err){

    int size = 1;
    char *str = malloc(sizeof(char));
    int i = 0;
    char c = fgetc(fp);
    while(!isspace(c)){
        str[i++] = c;
	if(i >= size) str = grow(str, &size);
        c = fgetc(fp);
    }

    lexeme_t *l = newLexeme();
    setLexemeValue(str, l);
    setLexemeType(ERROR, l);
    setLexemeError(err, l);

    return l;

}

lexeme_t *parseError(char *str, FILE *fp, char *err){

    int size = strlen(str);
    while(size > 0) ungetc(str[--size], fp);
    return lexError(fp, err);

}

char *grow(char *str, int *size){

    size *= 2;
    str = realloc(str, sizeof(char) * size);
    return str;

}