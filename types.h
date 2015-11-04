#ifndef types_h
#define types_h

typedef struct lenv lenv;
typedef struct lval lval;

typedef lval*(*lbuiltin)(lenv*, lval*);

struct lenv {
  int count;
  char** syms;
  lval** vals;
};

struct lval {
  int type;

  long num;
  char* err;
  char* sym;
  lbuiltin fun;

  int count;
  lval** cell;
};
#endif
