#include "util.h"

int main(void) {
  struct S s;
  init_s(s);

  overflow(s.str, (char *)&s.n2.l);
  s.n2.l;

  return 0;
}
