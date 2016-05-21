#ifndef types_h
#define types_h

typedef enum {
  Ty_sint
} type_kind;

typedef enum {
  Int_32
} int_kind;

typedef struct {
  type_kind kind;
  union {
    int_kind sint;
  } data;
} type;

type resolve(str name);

#endif
