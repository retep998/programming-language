#ifndef ast_h
#define ast_h

#include "common.h"
#include "types.h"

typedef enum {
  Expr_int_literal
} expression_kind;

typedef struct {
  expression_kind kind;
  union {
    struct {
      u64 value;
    } int_literal;
  } data;
} expression;

typedef enum {
  Stmt_return,
  Stmt_none
} statement_kind;

typedef struct {
  statement_kind kind;
  union {
    expression return_;
  } data;
} statement;

typedef struct {
  str name;
  type return_ty;
} function;

typedef struct {
  u8 _;
} ast;

ast ast_new(void);
void ast_add_function(ast* self, function func);

function function_new(str name, type return_ty);
void function_add_stmt(function* self, statement stmt);

#endif
