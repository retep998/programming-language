#include "lexer.h"

#include <stdio.h>
#include <ctype.h>

void token_kind_print(tokenKind kind) {
  switch (kind) {
    case Tok_keyword_fn:
      printf("keyword `fn`");
      break;
    case Tok_keyword_return:
      printf("keyword `return`");
      break;
    case Tok_identifier:
      printf("identifier");
      break;
    case Tok_integer:
      printf("integer");
      break;
    case Tok_open_paren:
      printf("`(`");
      break;
    case Tok_close_paren:
      printf("`)`");
      break;
    case Tok_open_brace:
      printf("`{`");
      break;
    case Tok_close_brace:
      printf("`}`");
      break;
    case Tok_semicolon:
      printf("`;`");
      break;
    case Tok_skinny_arrow:
      printf("`->`");
      break;
    case Tok_colon:
      printf("`:`");
      break;
    case Tok_eof:
      printf("`EOF`");
      break;
  }
}

void token_print(token const* tok) {
  switch (tok->kind) {
    case Tok_identifier:
      printf("identifier `"); str_print(tok->data.identifier); printf("`");
      break;
    case Tok_integer:
      printf("integer `%llu`", tok->data.integer.value);
      break;
    default:
      token_kind_print(tok->kind);
      break;
  }
}

token get_token(str_iter* iter) {
#define advance str_iter_advance(iter)
#define peek str_iter_peek(iter)
  token ret;
  char first;

  while(isspace(first = peek)) {
    advance;
  }

  // === words ===
  if (isalpha(first)) { // Identifier or Keyword
    str ident;
    ident.pointer = iter->data.pointer + iter->idx;
    ident.length = 1;
    advance;
    while (isalnum(peek)) {
      ++ident.length;
      advance;
    }
    if (str_eq(ident, str_from_lit("fn"))) {
      ret.kind = Tok_keyword_fn;
    } else if (str_eq(ident, str_from_lit("return"))) {
      ret.kind = Tok_keyword_return;
    } else {
      ret.kind = Tok_identifier;
      ret.data.identifier = ident;
    }
    return ret; // returns early so as to not deal with the automatic advance
                // at the bottom
  }

  // === numbers ===
  else if (isdigit(first)) { // number
    str ident;
    u64 number;
    ident.pointer = iter->data.pointer + iter->idx;
    ident.length = 1;
    advance;
    while (isdigit(peek)) {
      ++ident.length;
      advance;
    }
    if (str_parse_u64(ident, &number) == 0) {
      ret.kind = Tok_integer;
      ret.data.integer.value = number;
    } else {
      printf("Invalid number: ");
      str_print(ident);
      puts("");
      exit(1);
    }

    return ret;
  }

  // === operators ===
  else if (first == '-') {
    advance;
    if (peek == '>') {
      ret.kind = Tok_skinny_arrow;
    } else {
      printf("Operations are, as of yet, unsupported (-)");
      exit(1);
    }
  }

  // === delimiters ===
  else if (first == '(') {
    ret.kind = Tok_open_paren;
  } else if (first == ')') {
    ret.kind = Tok_close_paren;
  } else if (first == '{') {
    ret.kind = Tok_open_brace;
  } else if (first == '}') {
    ret.kind = Tok_close_brace;
  } else if (first == ';') {
    ret.kind = Tok_semicolon;
  }

  // === types ===
  else if (first == ':') {
    ret.kind = Tok_colon;
  }

  // === misc ===
  else if (first == -1) {
    ret.kind = Tok_eof;
  } else {
    printf("Unknown: `%c` (%d)\n", first, first);
    exit(1);
  }

  advance;
  return ret;
#undef advance
#undef peek
}

token eat_token(str_iter* iter, tokenKind kind) {
  token ret;
  ret = get_token(iter);
  if (ret.kind == kind) {
    return ret;
  } else {
    printf("Error: expected "); token_kind_print(kind); printf(", found ");
    token_print(&ret);
    exit(1);
  }
}

NORETURN
void token_error(str expected, token const* found) {
  printf("Error: expected ");
  str_print(expected);
  printf(", found ");
  token_print(found);
  puts("");
  exit(1);
}
