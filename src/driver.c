#include <stdio.h>

#include "common.c"
#include "ast.c"
#include "lexer.c"
#include "types.c"
#include "parse.c"

/* TODO(ubsan): real error handling */


static void compile(str_iter iter) {
#define advance (cur_tok = get_token(&iter))
  ast ast;
  token cur_tok;

  while (1) {
    switch (advance.kind) {
      case Tok_keyword_fn: {
        parse_function(&ast, &iter);
      } break;
      case Tok_eof: {
      } return;
      default: {
      } token_error(str_from_lit("item"), &cur_tok);
    }
  }
#undef advance
}

int main(void) {
  str program = str_from_lit(
    "fn main() -> s32 {\n"
    "  return 0;\n"
    "}\n"
  );

  compile(str_iter_new(program));

  return 0;
}
