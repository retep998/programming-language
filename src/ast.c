#include "ast.h"

ast ast_new(void) {
  ast ret;
  ret._ = 0;
  return ret;
}

void ast_add_function(ast* self, function func) {
  (void)self;
  (void)func;
}

function function_new(str name, type return_ty) {
  function ret;
  ret.name = name;
  ret.return_ty = return_ty;

  return ret;
}

void function_add_stmt(function* self, statement stmt) {
  (void)self;
  (void)stmt;
}
