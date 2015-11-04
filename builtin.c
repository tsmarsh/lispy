#include "builtin.h"

lval* builtin_head(lenv* e, lval* a) {
  LASSERT(a, a->count == 1,
    "Function 'head' passed too many arguments!");
  LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
    "Function 'head' passed incorrect type!");
  LASSERT(a, a->cell[0]->count != 0,
    "Function 'head' passed {}!");

  lval* v = lval_take(a, 0);  
  while (v->count > 1) { lval_del(lval_pop(v, 1)); }
  return v;
}

lval* builtin_tail(lenv* e, lval* a) {
  LASSERT(a, a->count == 1,
    "Function 'tail' passed too many arguments!");
  LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
    "Function 'tail' passed incorrect type!");
  LASSERT(a, a->cell[0]->count != 0,
    "Function 'tail' passed {}!");

  lval* v = lval_take(a, 0);  
  lval_del(lval_pop(v, 0));
  return v;
}

lval* builtin_list(lenv* e, lval* a) {
  a->type = LVAL_QEXPR;
  return a;
}

lval* builtin_join(lenv* e, lval* a) {

  for (int i = 0; i < a->count; i++) {
    LASSERT(a, a->cell[i]->type == LVAL_QEXPR,
      "Function 'join' passed incorrect type.");
  }

  lval* x = lval_pop(a, 0);

  while (a->count) {
    x = lval_join(x, lval_pop(a, 0));
  }

  lval_del(a);
  return x;
}

lval* builtin_eval(lenv* e, lval* a) {
  LASSERT(a, a->count == 1,
    "Function 'eval' passed too many arguments!");
  LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
    "Function 'eval' passed incorrect type!");

  lval* x = lval_take(a, 0);
  x->type = LVAL_SEXPR;
  return lval_eval(e, x);
}

lval* ensure_all_args_are_numbers(lval* a){
  for (int i = 0; i < a->count; i++) {
    if (a->cell[i]->type != LVAL_NUM) {
      lval_del(a);
      return lval_err("Cannot operate on non-number!");
    }
  }
  return a;
}

lval* builtin_add(lenv* e, lval* a) {    
  lval* numbers = ensure_all_args_are_numbers(a);
  if(numbers->type == LVAL_ERR) {
    return numbers;
  }
  
  lval* x = lval_pop(numbers, 0);

  while (a->count > 0) {

    lval* y = lval_pop(a, 0);
    x->num += y->num;
    lval_del(y);
  }

  lval_del(a);
  return x;
}

lval* builtin_sub(lenv* e, lval* a) {
  
  lval* numbers = ensure_all_args_are_numbers(a);
  if(numbers->type == LVAL_ERR) {
    return numbers;
  }
  
  lval* x = lval_pop(numbers, 0);

  if (a->count == 0) {
    x->num = -x->num;
  }

  while (a->count > 0) {

    lval* y = lval_pop(a, 0);
    x->num -= y->num;
    lval_del(y);
  }

  lval_del(a);
  return x;
}

lval* builtin_mul(lenv* e, lval* a) {
  
  lval* numbers = ensure_all_args_are_numbers(a);
  if(numbers->type == LVAL_ERR) {
    return numbers;
  }
  
  lval* x = lval_pop(numbers, 0);

  while (a->count > 0) {
    lval* y = lval_pop(a, 0);
    x->num *= y->num;
    lval_del(y);
  }

  lval_del(a);
  return x;
}

lval* builtin_div(lenv* e, lval* a) {
  
  lval* numbers = ensure_all_args_are_numbers(a);
  if(numbers->type == LVAL_ERR) {
    return numbers;
  }
  
  lval* x = lval_pop(numbers, 0);

  while (a->count > 0) {
    lval* y = lval_pop(a, 0);
    if (y->num == 0) {
      lval_del(x); lval_del(y);
      x = lval_err("Division By Zero!"); break;
    }
    x->num /= y->num;
    lval_del(y);
  }
  
  lval_del(a);
  return x;
}