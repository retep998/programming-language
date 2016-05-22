#ifndef ast_h
#define ast_h

#include "common.h"
#include "types.h"

typedef enum expression_kind {
  Expr_int_literal
} expression_kind;

typedef struct expression {
  union {
    struct {
      u64 value;
    } int_literal;
  } data;

  expression_kind kind;
} expression;

typedef enum statement_kind {
  Stmt_return,
  Stmt_none
} statement_kind;

typedef struct statement {
  union {
    expression return_;
  } data;

  statement_kind kind;
} statement;

typedef struct function {
  str name;
  type return_ty;
} function;

typedef struct ast {
  u8 _;
} ast;

ast ast_new(void);
void ast_add_function(ast* self, function func);

function function_new(str name, type return_ty);
void function_add_stmt(function* self, statement stmt);

#endif
