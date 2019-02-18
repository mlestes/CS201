/*****************************************************************************/
// lexer.h by Murray Estes
// A header file for a lexer ISO a custom programming language.
// ***************************************************************************/

#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdlib.h>
#include "lexeme.h"

lexeme_t *lex(FILE *fp);

#endif
