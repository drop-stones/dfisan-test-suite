#include "util.h"

int main(void) {
  struct S s;
  init_s(s);

  non_sequential_overread(s.n1.str1, (char *)&s.n2.l);

  return 0;
}
