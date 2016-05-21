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

ast ast_new();
void ast_collect_types(ast* ast, str_iter iter); // first pass
void ast_collect_function_types(ast* ast, str_iter iter); // second pass
void ast_collect_functions(ast* ast, str_iter iter); // second pass
void ast_build(ast* ast, str file);

function function_new(str name, type return_ty);

#endif
