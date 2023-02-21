// dfisan cannot detect the sub-object overflow
// because svf think struct S as Field-insensitive objects (by for-loop in Input()).

#include "util.h"

void Input(char *str, char *dst) {
  overflow(str, dst);
}

int main(void) {
  struct User u = { "Alice", 100 };

  Input(u.name, &u.id); // Sub-object overflow
  u.id;

  return 0;
}
