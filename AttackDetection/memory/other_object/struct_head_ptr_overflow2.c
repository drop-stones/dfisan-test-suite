#include "util.h"

void Input(char *str, char *dst) {
  overflow(str, dst);
}

int main(void) {
  struct User u = { "Alice", 200 };
  int x = 100;

  Input(u.name, &x);
  x;

  return 0;
}
