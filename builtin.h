#ifndef builtin_h
#define builtin_h

#include "lval.h"

#define LASSERT(args, cond, fmt, ...) \
  if (!(cond)) { \
    lval* err = lval_err(fmt, ##__VA_ARGS__); \
    lval_del(args); \
    return err; \
  }

#define LASSERT_TYPE(func, args, index, expect)    \
  LASSERT(args, args->cell[index]->type == expect, \
    "Function '%s' passed incorrect type for argument %i. " \
    "Got %s, Expected %s.", \
    func, index, ltype_name(args->cell[index]->type), ltype_name(expect))

#define LASSERT_NUM(func, args, num) \
  LASSERT(args, args->count == num, \
    "Function '%s' passed incorrect number of arguments. " \
    "Got %i, Expected %i.", \
    func, args->count, num)

#define LASSERT_NOT_EMPTY(func, args, index) \
  LASSERT(args, args->cell[index]->count != 0, \
    "Function '%s' passed {} for argument %i.", func, index);

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

lval* builtin_put(lenv* e, lval* a);

lval* builtin_var(lenv* e, lval* a, char* func);

lval* builtin_lambda(lenv* e, lval* a);

char* ltype_name(int t);
#endif
