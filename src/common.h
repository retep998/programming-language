#ifndef common_h
#define common_h

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#if _MSC_VER >= 1310
  // MS Visual Studio 2003/.NET Framework 1.1 or newer
#define NORETURN __declspec( noreturn);
#elif __GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ >= 5))
  // GCC 2.5 or newer
#define NORETURN __attribute__((noreturn))
#elif __STDC_VERSION__ >= 201112L
#define NORETURN _Noreturn
#else
#error "This project requires a way to do noreturn in order to build"
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t usize;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef ptrdiff_t ssize;

typedef struct {
  usize length;
  usize capacity;
  // NOT nul terminated
  char* pointer;
} string;
typedef struct {
  usize length;
  char const* pointer;
} str;

typedef struct {
  str data;
  usize idx;
} str_iter;

string string_from_cstr(char const* str);
string string_from_str(str str);
str string_str(string const* self);
void string_push(string* self, char c);
void string_free(string self);
void string_print(string const* self);

// must be freed afterwards!
char* str_cstr(str self);
void str_print(str self);

// 1 if equal, 0 if not
int str_eq(str lhs, str rhs);

// returns 0 if successfully parsed
int str_parse_u64(str from, u64* to);

str str_from_raw_parts(char const* s, usize length);

#define str_from_lit(s) str_from_raw_parts(s "", sizeof(s) - 1)

str_iter str_iter_new(str s);
// returns the next char, or -1 if EOF
int str_iter_advance(str_iter* self);
// returns the next char, or -1 if EOF
int str_iter_peek(str_iter const* self);

#endif
