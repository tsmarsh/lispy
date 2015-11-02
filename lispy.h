#include "mpc.h"

#define OPERATOR 1
#define THIRD_CHILD 2

#define LASSERT(args, cond, err) \
  if (!(cond)) { lval_del(args); return lval_err(err); }

char* GRAMMER = 
  "                                                        \
    number : /-?[0-9]+/ ;                                  \
    symbol : \"list\" | \"head\" | \"tail\"                \
           | \"join\" | \"eval\" | '+' | '-' | '*' | '/' ; \
    sexpr  : '(' <expr>* ')' ;                             \
    qexpr  : '{' <expr>* '}' ;                             \
    expr   : <number> | <symbol> | <sexpr> | <qexpr> ;     \
    lispy  : /^/ <expr>* /$/ ;                             \
  ";

typedef struct lval {
  int type;
  long num;

  char* err;
  char* sym;

  int count;
  struct lval** cell;
} lval;

enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR };

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

lval* lval_qexpr(void);

lval* lval_eval_sexpr(lval* v);

lval* lval_take(lval* v, int i);

lval* lval_join(lval* x, lval* y); 

lval* builtin_op(lval* a, char* op);

lval* builtin_head(lval* a);

lval* builtin_tail(lval* a);

lval* builtin_list(lval* a);

lval* builtin_join(lval* a);

lval* builtin(lval* a, char* func);
