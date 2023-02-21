#include "util.h"

int main(void) {
  struct S s = { "", { "", 100, 200 }, { "", 300, 400 } };
  int x = 500;

  overflow(s.str, (char *)&x);
  x;

  return 0;
}
