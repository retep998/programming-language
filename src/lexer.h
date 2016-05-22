#ifndef token_h
#define token_h

#include "common.h"

typedef enum token_kind {
  // words
  Tok_keyword_fn,
  Tok_keyword_return,
  Tok_identifier,

  // numbers
  Tok_integer,

  // delimiters
  Tok_open_paren,
  Tok_close_paren,
  Tok_open_brace,
  Tok_close_brace,
  Tok_semicolon,

  // types
  Tok_skinny_arrow,
  Tok_colon,

  // eof
  Tok_eof
} tokenKind;

typedef struct token {
  union {
    str identifier;
    struct {
      u64 value;
    } integer;
  } data;

  tokenKind kind;
} token;

void token_kind_print(tokenKind kind);

void token_print(token const* tok);

token get_token(str_iter* iter);
token eat_token(str_iter* iter, tokenKind kind);

NORETURN void token_error(str expected, token const* found);

#endif
