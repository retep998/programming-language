#include "parse.h"
#include "lexer.h"
#include "types.h"
#include "ast.h"

#include <stdio.h>

/* NOTE(ubsan): SEE THESE MACROS! the code below will be very confusing if you
   don't
 */
#define advance (cur_tok = get_token(iter))
#define eat(kind) (cur_tok = eat_token(iter, (kind)))

static expression parse_expression(str_iter* iter) {
  expression expr;
  token cur_tok;

  switch (advance.kind) {
    case Tok_integer:
      expr.kind = Expr_int_literal;
      expr.data.int_literal.value = cur_tok.data.integer.value;
      eat(Tok_semicolon);
      break;
    default:
      token_error(str_from_lit("expression"), &cur_tok);
  }

  return expr;
}

static statement parse_stmt(str_iter* iter) {
  statement stmt;
  token cur_tok;

  switch (advance.kind) {
    case Tok_keyword_return: {
      stmt.kind = Stmt_return;
      stmt.data.return_ = parse_expression(iter);
    } break;
    case Tok_close_brace: {
      stmt.kind = Stmt_none;
    } break;
    default: {
    } token_error(str_from_lit("statement"), &cur_tok);
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
  eat(Tok_identifier); /* return type */
  return_ty = resolve(cur_tok.data.identifier);
  eat(Tok_open_brace);

  func = function_new(name, return_ty);

  while (1) {
    statement cur_stmt;
    switch ((cur_stmt = parse_stmt(iter)).kind) {
      case Stmt_return: {
        function_add_stmt(&func, cur_stmt);
      } break;
      case Stmt_none: {
        ast_add_function(ast, func);
      } return;
    }
  }
}
#undef advance
#undef eat
