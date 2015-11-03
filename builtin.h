#ifndef builtin_h
#define builtin_h

#include "lval.h"

#define LASSERT(args, cond, err) \
  if (!(cond)) { lval_del(args); return lval_err(err); }

lval* builtin_op(lval* a, char* op);

lval* builtin_head(lval* a);

lval* builtin_tail(lval* a);

lval* builtin_list(lval* a);

lval* builtin_join(lval* a);

lval* builtin(lval* a, char* func);

#endif
