#ifndef lval_h
#define lval_h

#include "mpc.h"
#include "types.h"
#include "lenv.h"

enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR, LVAL_FUN};

enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

lval* eval_op(lval x, char* op, lval y);

lval* eval(mpc_ast_t* t);

void lval_print(lval* v);

void lval_println(lval* v);

void lval_del(lval* v);

lval* lval_eval(lenv* e, lval* v);

lval* lval_read_num(mpc_ast_t* t);

lval* lval_read(mpc_ast_t* t);

lval* lval_add(lval* v, lval* x);

lval* lval_pop(lval* v, int i);

lval* lval_sym(char* s);

lval* lval_sexpr(void);

lval* lval_qexpr(void);

lval* lval_eval_sexpr(lenv* e, lval* v);
  
lval* lval_take(lval* v, int i);

lval* lval_join(lval* x, lval* y);

lval* lval_fun(lbuiltin func);

lval* lval_copy(lval* v);

lval* lval_err(char* fmt, ...);

lval* lval_lambda(lval* formals, lval* body);

lval* lval_call(lenv* e, lval* f, lval* a);
#endif
