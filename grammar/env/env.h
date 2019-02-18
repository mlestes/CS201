/*****************************************************************************/
// env.h by Murray Estes
// A header file for implementing environment functionality for ESL.
/*****************************************************************************/

#ifndef __ENV_H__
#define __ENV_H__

#include <stdlib.h>
#include "../lex/lexeme.h"

#define ENV     100
#define JOIN    101
#define VALUE   102

lexeme_t *newEnv(void);
lexeme_t *lookup(lexeme_t *var, lexeme_t *env);
lexeme_t *update(lexeme_t *var, lexeme_t *val, lexeme_t *env);
lexeme_t *insert(lexeme_t *var, lexeme_t *val, lexeme_t *env);
lexeme_t *extend(lexeme_t *var, lexeme_t *val, lexeme_t *env);
void print_env(FILE *, lexeme_t *, int);

#endif
