#include "util.h"

int main(void) {
  struct S s;
  init_s(s);

  overflow(s.n1.str1, (char *)&s.n2.l);
  s.n2.l;

  return 0;
}
