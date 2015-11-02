#include "mpc.h"

#define OPERATOR 1
#define THIRD_CHILD 2

typedef struct {
  int type;
  long num;
  int err;
} lval;

lval eval_op(lval x, char* op, lval y);

lval eval(mpc_ast_t* t);

void lval_print(lval v);

void lval_println(lval v);
