#include "parse.h"
#include "lexer.h"
#include "types.h"
#include "ast.h"

#include <stdio.h>

// NOTE(ubsan): SEE THESE MACROS! the code below will be very confusing if you
// don't
#define advance (cur_tok = get_token(iter))
#define eat(kind) (cur_tok = eat_token(iter, (kind)))

expression parse_expression(str_iter* iter) {
  expression expr;
  token cur_tok;

  switch (advance.kind) {
    case Tok_integer:
      expr.kind = Expr_int_literal;
      expr.data.int_literal.value = cur_tok.data.integer.value;
    default:
      token_error(str_from_lit("expression"), &cur_tok);
  }
}

statement parse_stmt(str_iter* iter) {
  statement stmt;
  token cur_tok;

  switch (advance.kind) {
    case Tok_keyword_return:
      stmt.kind = Stmt_return;
      stmt.data.return_ = parse_expression(iter);
      break;
    case Tok_close_brace:
      stmt.kind = Stmt_none;
    default:
      printf("Error: expected statement, found ");
      token_print(&cur_tok);
      exit(1);
  }
  return stmt;
}

void parse_function(ast* ast, str_iter* iter) {
  token cur_tok;
  str name;
  type return_ty;
  function func;

  eat(Tok_identifier);
  name = cur_tok.data.identifier;
  eat(Tok_open_paren); eat(Tok_close_paren);
  eat(Tok_skinny_arrow);
  eat(Tok_identifier); // return type
  return_ty = resolve(cur_tok.data.identifier);
  eat(Tok_open_brace);

  func = function_new(name, return_ty);

  while (1) {
  }

  (void)ast;
}
#undef advance
#undef eat
