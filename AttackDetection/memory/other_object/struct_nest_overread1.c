#include "util.h"

int main(void) {
  struct S s = { "", { "", 100, 200 }, { "", 300, 400 } };
  int x = 500;

  overread(s.str, &x);

  return 0;
}
