#include "mpc.h"

#define OPERATOR 1
#define THIRD_CHILD 2

typedef struct lval {
  int type;
  long num;

  char* err;
  char* sym;

  int count;
  struct lval** cell;
} lval;

enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR };

enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

lval* eval_op(lval x, char* op, lval y);

lval* eval(mpc_ast_t* t);

void lval_print(lval* v);

void lval_println(lval* v);

void lval_del(lval* v);

lval* lval_read_num(mpc_ast_t* t);

lval* lval_read(mpc_ast_t* t);

lval* lval_add(lval* v, lval* x);

lval* lval_err(char* m);

lval* lval_sym(char* s);

lval* lval_sexpr(void);
