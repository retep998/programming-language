#include "types.h"

type resolve(str name) {
  type ret;
  if (str_eq(name, str_from_lit("s32"))) {
    ret.kind = Ty_sint;
    ret.data.sint = Int_32;
  } else {
    printf("Error: unknown type: "); str_print(name); puts("");
    exit(1);
  }

  return ret;
}
