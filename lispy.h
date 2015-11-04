#include "mpc.h"
#include "lval.h"

#define OPERATOR 1
#define THIRD_CHILD 2

char* GRAMMER = 
  "                                                        \
    number : /-?[0-9]+/ ;                                  \
    symbol : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/ ;            \
    sexpr  : '(' <expr>* ')' ;                             \
    qexpr  : '{' <expr>* '}' ;                             \
    expr   : <number> | <symbol> | <sexpr> | <qexpr> ;     \
    lispy  : /^/ <expr>* /$/ ;                             \
  ";


