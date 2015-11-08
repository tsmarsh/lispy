#include "builtin.h"

lval* builtin_head(lenv* e, lval* a) {
  LASSERT(a, a->count == 1,
          "Function 'head' passed too many arguments!",
          "Got %i, expected %i", a->count, 1);
  LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
          "Function 'head' passed incorrect type!",
          "Got %i, expected %i", a->cell[0]->type, LVAL_QEXPR);
  LASSERT(a, a->cell[0]->count != 0,
          "Function 'head' passed {}!",
          "List is empty");

  lval* v = lval_take(a, 0);  
  while (v->count > 1) { lval_del(lval_pop(v, 1)); }
  return v;
}

lval* builtin_tail(lenv* e, lval* a) {
  LASSERT(a, a->count == 1,
          "Function 'tail' passed too many arguments!");
  LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
          "Function 'tail' passed incorrect type!",
          "Expected LVAL_QEXPR got %i", a->cell[0]->type);
  LASSERT(a, a->cell[0]->count != 0,
          "Function 'tail' passed {}!",
          "Count was: %i", a->cell[0]->count);

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
            "Function 'join' passed incorrect type.",
            "Expected {} but got %i", a->cell[i]->type);
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

lval* builtin_def(lenv* e, lval* a) {
  return builtin_var(e, a, "def");
}

lval* builtin_put(lenv* e, lval* a) {
  return builtin_var(e, a, "=");
}

lval* builtin_var(lenv* e, lval* a, char* func) {
  LASSERT_TYPE(func, a, 0, LVAL_QEXPR);
  
  lval* syms = a->cell[0];
  
  for (int i = 0; i < syms->count; i++) {
    LASSERT(a, (syms->cell[i]->type == LVAL_SYM),
      "Function '%s' cannot define non-symbol. "
      "Got %s, Expected %s.", func, 
      ltype_name(syms->cell[i]->type),
      ltype_name(LVAL_SYM));
  }
  
  LASSERT(a, (syms->count == a->count-1),
    "Function '%s' passed too many arguments for symbols. "
    "Got %i, Expected %i.", func, syms->count, a->count-1);
    
  for (int i = 0; i < syms->count; i++) {
    /* If 'def' define in globally. If 'put' define in locally */
    if (strcmp(func, "def") == 0) {
      lenv_def(e, syms->cell[i], a->cell[i+1]);
    }
    
    if (strcmp(func, "=")   == 0) {
      lenv_put(e, syms->cell[i], a->cell[i+1]);
    } 
  }
  
  lval_del(a);
  return lval_sexpr();
}

lval* builtin_lambda(lenv* e, lval* a) {
  LASSERT_NUM("\\", a, 2);
  LASSERT_TYPE("\\", a, 0, LVAL_QEXPR);
  LASSERT_TYPE("\\", a, 1, LVAL_QEXPR);
  
  for (int i = 0; i < a->cell[0]->count; i++) {
    LASSERT(a, (a->cell[0]->cell[i]->type == LVAL_SYM),
      "Cannot define non-symbol. Got %s, Expected %s.",
      ltype_name(a->cell[0]->cell[i]->type),ltype_name(LVAL_SYM));
  }
  
  lval* formals = lval_pop(a, 0);
  lval* body = lval_pop(a, 0);
  lval_del(a);
  
  return lval_lambda(formals, body);
}

char* ltype_name(int t) {
  switch(t) {
    case LVAL_FUN: return "Function";
    case LVAL_NUM: return "Number";
    case LVAL_ERR: return "Error";
    case LVAL_SYM: return "Symbol";
    case LVAL_SEXPR: return "S-Expression";
    case LVAL_QEXPR: return "Q-Expression";
    default: return "Unknown";
  }
}
