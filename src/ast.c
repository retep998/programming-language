#include "ast.h"

ast ast_new() {
  ast ret;
  ret._ = 0;
  return ret;
}

void ast_collect_types(ast* ast, str_iter iter) {
  (void)ast;
  (void)iter;
}

void ast_collect_function_types(ast* ast, str_iter iter) {
  (void)ast;
  (void)iter;
}

void ast_collect_functions(ast* ast, str_iter iter) {
  (void)ast;
  (void)iter;
}

void ast_build(ast* ast, str file) {
  (void)ast;
  (void)file;
}
