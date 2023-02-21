#include "util.h"

int main(void) {
  struct User u = { "Alice", 200 };
  int x = 100;

  overread(u.name, &x);

  return 0;
}
