#include "common.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

string string_from_cstr(char const* str) {
  string ret;

  ret.length = ret.capacity = strlen(str);
  ret.pointer = malloc(ret.capacity);
  memcpy(ret.pointer, str, ret.length);
  return ret;
}

string string_from_str(str str) {
  string ret;

  ret.length = ret.capacity = str.length;
  ret.pointer = malloc(ret.capacity);
  memcpy(ret.pointer, str.pointer, ret.length);
  return ret;
}

string string_new() {
  string ret = {0, 0, NULL};
  return ret;
}

str string_str(string const* string) {
  str ret;
  ret.length = string->length;
  ret.pointer = string->pointer;
  return ret;
}

void string_push(string* self, char c) {
  if (self->length + 1 == self->capacity) {
    self->pointer = realloc(self->pointer, self->capacity * 2);
    if (self->pointer == NULL) {
      exit(255);
    }
    self->capacity *= 2;
  }
  self->pointer[self->length] = c;
  self->length += 1;
}

void string_free(string self) {
  free(self.pointer);
}

void string_print(string const* self) {
  str_print(string_str(self));
}


char* str_cstr(str string) {
  char* ret = malloc(string.length + 1);
  memcpy(ret, string.pointer, string.length);
  ret[string.length] = '\0';
  return ret;
}

void str_print(str string) {
  char const* start = string.pointer;
  char const* end = string.pointer + string.length;

  for(; start < end; ++start) {
    putchar(*start);
  }
}

str str_from_raw_parts(char const* s, usize length) {
  str ret;
  ret.pointer = s;
  ret.length = length;
  return ret;
}

// 1 if equal, 0 if not
int str_eq(str lhs, str rhs) {
  if (lhs.length != rhs.length) {
    return 0;
  }

  if (memcmp(lhs.pointer, rhs.pointer, lhs.length) == 0) {
    return 1;
  } else {
    return 0;
  }
}

// returns 0 if successfully parsed
int str_parse_u64(str from, u64* to) {
  usize i;
  *to = 0;
  for (i = 0; i < from.length; ++i) {
    if (!isdigit(from.pointer[i])) {
      return -1;
    }
    *to = *to * 10 + from.pointer[i] - '0';
  }
  return 0;
}



str_iter str_iter_new(str s) {
  str_iter ret;
  ret.data = s;
  ret.idx = 0;
  return ret;
}

int str_iter_advance(str_iter* self) {
  int ret = -1;
  if (self->idx < self->data.length) {
    ret = self->data.pointer[self->idx++];
  }
  return ret;
}

int str_iter_peek(str_iter const* self) {
  int ret = -1;
  if (self->idx < self->data.length) {
    ret = self->data.pointer[self->idx];
  }
  return ret;
}
