#include "util.h"

int main(void) {
  struct User u = { "Alice", 200 };
  int x = 100;

  overflow(u.name, &x);
  x;    // Error: x is broken

  return 0;
}