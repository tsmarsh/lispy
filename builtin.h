#ifndef builtin_h
#define builtin_h

#include "lval.h"

#define LASSERT(args, cond, err) \
  if (!(cond)) { lval_del(args); return lval_err(err); }

lval* builtin_head(lenv* e, lval* a);

lval* builtin_tail(lenv* e, lval* a);

lval* builtin_list(lenv* e, lval* a);

lval* builtin_join(lenv* e, lval* a);

lval* builtin(lenv* e, lval* a, char* func);

lval* builtin_add(lenv* e, lval* a);

lval* builtin_sub(lenv* e, lval* a);

lval* builtin_mul(lenv* e, lval* a);

lval* builtin_div(lenv* e, lval* a);

lval* builtin_eval(lenv* e, lval* a);

lval* builtin_def(lenv* e, lval* a);
#endif
